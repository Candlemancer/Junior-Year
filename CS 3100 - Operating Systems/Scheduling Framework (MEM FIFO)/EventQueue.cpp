// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// Event Queue Implementation

#include "EventQueue.hpp"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include "CandleStats.hpp"

#include "FIFOQueue.hpp"
#include "RoundRobinQueue.hpp"
#include "ShortestJobQueue.hpp"
#include "ApproxShortestQueue.hpp"
#include "FIFOTable.hpp"

EventQueue::EventQueue(
	double frequency, 
	double mixRate, 
	double contextCost, 
	double pgFaultCost,
	int numCPUs, 
	int numIOs,
	int numPages,
	int algorithm,
	double quantumSize) :
	contextSwitchCost(contextCost),
	pageFaultCost(pgFaultCost),
	resourcesUsed(0),
	totalResources(numCPUs/* + numIOs*/),
	device(numCPUs, numIOs),
	throughput(0) {
	
	// std::cout << "Device CPUs: " << device.getNumCPUs() << " Device IOs: " << device.getNumIOs() << std::endl;
	generateTasks(frequency, mixRate, numIOs);

	// Create a Terminate Event
	events.push(Event(Event::END_PROCESS, runningTime + 1.0));

	// Create the Ready Queue
	rqueue = std::unique_ptr<ReadyQueue>();
	switch (algorithm) {
		case 1:
			rqueue = std::unique_ptr<ReadyQueue>(new FIFOQueue());
			break;
		case 2:
			rqueue = std::unique_ptr<ReadyQueue>(new RoundRobinQueue(quantumSize));
			break;
		case 3:
			rqueue = std::unique_ptr<ReadyQueue>(new ShortestJobQueue());
			break;
		case 4:
			rqueue = std::unique_ptr<ReadyQueue>(new ApproxShortestQueue());
			break;
		default:
			rqueue = std::unique_ptr<ReadyQueue>(new FIFOQueue());
	}

	// Create the Page Table
	pgTable = std::unique_ptr<PageTable>(new FIFOTable(numPages));

	update();

	return;	
}

void EventQueue::generateTasks(double frequency, double mixRate, int numIOs) {

	// Generate tasks
	auto numTasks = runningTime / frequency;

	std::fill_n(back_inserter(taskStartTimes), numTasks, -1.0);
	std::fill_n(back_inserter(taskResponseTimes), numTasks, -1.0);
	std::fill_n(back_inserter(taskFinishTimes), numTasks, -1.0);

	std::generate_n(back_inserter(allTasks), numTasks, [&](){ return Task(mixRate, numIOs); });

	// Report on tasks Created
	// std::cout << "==============================================" << std::endl;
	// std::cout << "Generated the following Tasks:" << std::endl;
	// for (auto&& i : allTasks){
	// 	std::cout << "Task with " << i.getTasks().size() << " steps." << std::endl;
	// }
	// std::cout << "==============================================" << std::endl;

	// Create Start Events for all the tasks.
	for (unsigned int i = 0; i < allTasks.size(); ++i) {
		events.push(Event(Event::TASK_START, i * frequency, 0.0, i));
		taskStartTimes[i] = i * frequency;
	}

	return;
}

void EventQueue::update() {

	while (true) {

		// Read the top event
		auto ev = events.top();
		events.pop();

		// Terminate the simulation
		if (ev.m_taskType == Event::END_PROCESS) { 
			computeThroughput();
			computeLatency();
			computeResponseTimes();

			return; }

		// Skip all NO_OP Events
		if (ev.m_taskType == Event::NO_OP) { continue; }

		// Calculate Start Times
		if (ev.m_taskType == Event::TASK_START) {
			taskStartTimes[ev.m_taskNumber] = ev.m_startTime;
			completeStep(ev);
			continue;
		}

		// Calculate Finish Times
		if (ev.m_taskType == Event::TASK_STOP) {
			taskFinishTimes[ev.m_taskNumber] = ev.m_startTime;
			continue;
		}


		// Update Progress
		computeUtilization();
		// std::cout << std::get<0>(ev) << "ms" << " - " << 
		// 	"Task " << std::get<1>(ev) << ": "  << 
		// 	"(Dev: " << std::get<2>(ev) << ", Dur: " << std::get<3>(ev) << ")" << std::endl;

		// CPU Tasks
		if (ev.m_taskType == Event::CPU_START) {
			// printEvent(ev);
			pushReadyQueue(ev);
		}
		if (ev.m_taskType == Event::CPU_STOP) {
			device.freeCPU();
			resourcesUsed--;
			popReadyQueue(ev.m_startTime);	
			completeStep(ev);		
		}

		// IO Tasks
		if (ev.m_taskType == Event::IO_START) {
			// printEvent(ev);
			pushIOQueue(ev);
		}
		if (ev.m_taskType == Event::IO_STOP) {
			// Update Response Times
			if (taskResponseTimes[ev.m_taskNumber] == -1.0) {
				taskResponseTimes[ev.m_taskNumber] = ev.m_startTime;
			}
			// resourcesUsed--;
			popIOQueue(ev.m_idRequested, ev.m_startTime);
			completeStep(ev);
		}

		// Memory Tasks
		if (ev.m_taskType == Event::MEM_FETCH) {
			// printEvent(ev);
			fetchMemory(ev);
		}


	}

	// std::cout << "-------------------------------" << std::endl;

}

void EventQueue::pushReadyQueue(Event item) {

	rqueue->push(item);

	if (device.getNumCPUs() > 0) {
		popReadyQueue(item.m_startTime);
		return;
	}

	// std::cout << "	Task " << std::get<1>(item) << 
	// " waiting for free CPU. Time: " << std::get<0>(item) << std::endl;

	return;
}

void EventQueue::popReadyQueue(double currentTime) {

	auto item = rqueue->pop();

	// If Queue is empty
	if (item.m_taskType == Event::NO_OP) { return; }

	device.useCPU();
	resourcesUsed++;

	// Push a CPU Stop event
	events.push(
		Event(
			Event::CPU_STOP,
			currentTime + item.m_duration + contextSwitchCost,
			0.0,
			item.m_taskNumber
		)
	);

	// completeStep(item, currentTime);
	return;
}

void EventQueue::pushIOQueue(Event item) {
	device.pushIO(item.m_idRequested, item);
	// resourcesUsed++;

	if (device.getIOSize(item.m_idRequested) == 1) {
		popIOQueue(item.m_idRequested, item.m_startTime);
		return;
	}

	// std::cout << "	Task " << std::get<1>(item) << " waiting for IO Device " << 
	// id << ". Time: " << std::get<0>(item) << std::endl;

	return;
}

void EventQueue::popIOQueue(int id, double currentTime) {
	auto item = device.popIO(id);

	// If Queue is empty
	if (item.m_taskType == Event::NO_OP) { return; }

	// std::cout << "There are " << device.getIOSize(id) << 
	// " steps waiting on IO Device " << id << "." << std::endl;

	// Push an IO Stop Event
	events.push(
		Event(
			Event::IO_STOP,
			currentTime + item.m_duration + contextSwitchCost,
			0.0,
			item.m_taskNumber,
			item.m_idRequested
		)
	);
	
	return;
}

void EventQueue::fetchMemory(Event item) {

	if (pgTable->fetch(item)) { completeStep(item); return; }

	// Otherwise Page Fault
	// std::cout << "Page Fault while Accessing page " << item.m_idRequested << " from task " << item.m_taskNumber << std::endl;
	events.push(
		Event(
			Event::MEM_FETCH,
			item.m_startTime + pageFaultCost,
			item.m_duration,
			item.m_taskNumber,
			item.m_idRequested
		)
	);
	return;
}

// Gets the next event
void EventQueue::completeStep(Event item) {

	// If task is finished
	if (allTasks[item.m_taskNumber].size() == 0) { 
		events.push(
			Event(
				Event::TASK_STOP,
				item.m_startTime,
				0.0,
				item.m_taskNumber,
				item.m_idRequested
			)
		);

		return;
	}

	// Create a start event for the next step.
	auto nextTask = allTasks[item.m_taskNumber].pop();

	if (std::get<0>(nextTask) == -1) {
		events.push(
			Event(
				Event::CPU_START,
				item.m_startTime,
				std::get<1>(nextTask),
				item.m_taskNumber
			)
		);
	}
	if (std::get<0>(nextTask) == -2) {
		events.push(
			Event(
				Event::MEM_FETCH,
				item.m_startTime,
				0.0,
				item.m_taskNumber,
				std::get<1>(nextTask)
			)
		);
	}
	if (std::get<0>(nextTask) >= 0) {
		events.push(
			Event(
				Event::IO_START,
				item.m_startTime,
				std::get<1>(nextTask),
				item.m_taskNumber,
				std::get<0>(nextTask)
			)
		);
	}

	return;
}

void EventQueue::computeThroughput() {

	throughput = 0;
	for (unsigned int i = 0; i < taskStartTimes.size(); ++i) {
		if (taskStartTimes[i] == -1.0 || taskFinishTimes[i] == -1.0) { continue; }
		throughput++;
	}

	return;
}

void EventQueue::printThroughput() {

	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "Throughput Statistics:" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "Started " << taskStartTimes.size() << " tasks in " << runningTime << " time units." << std::endl;
	std::cout << "Completed " << throughput << " tasks in " << runningTime << " time units." << std::endl;
	std::cout << std::endl;
	std::cout << "Task Completion Percent: " << (throughput / (taskStartTimes.size() * 1.0) * 100.0) << "%" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << std::endl << std::endl;

	return;
}

void EventQueue::computeLatency() {

	for (unsigned int i = 0; i < taskStartTimes.size(); ++i) {
		if (taskStartTimes[i] == -1.0 || taskFinishTimes[i] == -1.0) { continue; }
		latency.push_back(taskFinishTimes[i] - taskStartTimes[i]);
	}

	if (latency.size() == 0) {
		latency.push_back(-1.0);
	}

	return;
}

void EventQueue::printLatency() {

	CandleStats latencyStats(latency);

	// for (auto&& i : latency) {
	// 	std::cout << "latency: " << i << std::endl;
	// }

	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "Latency Statistics:" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "Mean Latency: " << latencyStats.getMean() << std::endl;
	std::cout << "Minimum Latency:" << *std::min_element(latency.begin(), latency.end()) << std::endl;
	std::cout << "Maximum Latency: " << *std::max_element(latency.begin(), latency.end()) << std::endl;
	std::cout << "Latency Std. Dev.: " << latencyStats.getStandardDeviation() << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << std::endl << std::endl;

	return;
}

void EventQueue::computeResponseTimes() {

	for (unsigned int i = 0; i < taskStartTimes.size(); ++i) {
		if (taskStartTimes[i] == -1.0 || taskResponseTimes[i] == -1.0) { continue; }
		responses.push_back(taskResponseTimes[i] - taskStartTimes[i]);
	}

	if (responses.size() == 0) {
		responses.push_back(-1.0);
	}

	return;
}

void EventQueue::printResponseTimes() {

	CandleStats ResponseStats(responses);

	// for (auto&& i : responses) {
	// 	std::cout << "responses: " << i << std::endl;
	// }

	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "Response Time Statistics:" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "Mean Response Time: " << ResponseStats.getMean() << std::endl;
	std::cout << "Minimum Response Time: " << *std::min_element(responses.begin(), responses.end()) << std::endl;
	std::cout << "Maximum Response Time: " << *std::max_element(responses.begin(), responses.end()) << std::endl;
	std::cout << "Response Time Std. Dev.: " << ResponseStats.getStandardDeviation() << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << std::endl << std::endl;

	return;
}

void EventQueue::computeUtilization() {

	utilization.push_back(resourcesUsed * 1.0 / totalResources * 1.0);

	return;
}

void EventQueue::printUtilization() {

	CandleStats utilizationStats(utilization);

	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "Utilization Statistics:" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "Mean Utilization: " << utilizationStats.getMean() * 100.0 << "%" << std::endl;
	std::cout << "Minimum Utilization:" << *std::min_element(utilization.begin(), utilization.end()) * 100.0 << "%" << std::endl;
	std::cout << "Maximum Utilization: " << *std::max_element(utilization.begin(), utilization.end()) * 100.0 << "%" << std::endl;
	std::cout << "Utilization Std. Dev.: " << utilizationStats.getStandardDeviation() * 100.0 << "%" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << std::endl << std::endl;

	return;
}

void EventQueue::printEvent(Event item) {

	std::cout   << std::setw(8) << std::left << item.m_startTime << "ms" << " - " << 
		"Type " << std::setw(8) << std::left << item.m_taskType << " " <<
		"Task " << std::setw(8) << std::left << item.m_taskNumber << " " <<
		"Dur. " << std::setw(8) << std::left << item.m_duration << " " <<
		"IOid " << std::setw(8) << std::left << item.m_idRequested << std::endl;

	return;
}

void EventQueue::printStartTimes() {

	for (unsigned int i = 0; i < taskStartTimes.size(); ++i) {
		std::cout << "Task: " << i << " started at: " << taskStartTimes[i] << std::endl;
	}

	return;
}

void EventQueue::printFinishTimes() {

	for (unsigned int i = 0; i < taskFinishTimes.size(); ++i) {
		std::cout << "Task: " << i << " finished at: " << taskFinishTimes[i] << std::endl;
	}

	return;
}

