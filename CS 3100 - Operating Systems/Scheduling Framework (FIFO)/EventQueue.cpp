// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// Event Queue Implementation

#include "EventQueue.hpp"

#include <algorithm>
#include <iostream>
#include "CandleStats.hpp"

#include "FIFOQueue.hpp"

EventQueue::EventQueue(
	double frequency, 
	double mixRate, 
	double contextCost, 
	int numCPUs, 
	int numIOs) :
	contextSwitchCost(contextCost),
	resourcesUsed(0),
	totalResources(numCPUs + numIOs),
	device(numCPUs, numIOs) {
	
	// std::cout << "Device CPUs: " << device.getNumCPUs() << " Device IOs: " << device.getNumIOs() << std::endl;
	generateTasks(frequency, mixRate, numIOs);

	// Create a Terminate Event
	events.push(std::make_tuple(runningTime + 1, -1, -100, 0.0));
	rqueue = std::unique_ptr<ReadyQueue>(new FIFOQueue());
	update();
	
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
		events.push(std::make_tuple(i * frequency, i, -100, 0.1));
		taskStartTimes.at(i) = i * frequency;
	}

	return;
}

void EventQueue::update() {

	while (std::get<0>(events.top()) <= runningTime) {

		// Read the top event
		auto ev = events.top();
		events.pop();
		taskFinishTimes.at(std::get<1>(ev)) = std::get<0>(ev);
		calculateUtilization();

		// std::cout << std::get<0>(ev) << "ms" << " - " << 
		// 	"Task " << std::get<1>(ev) << ": "  << 
		// 	"(Dev: " << std::get<2>(ev) << ", Dur: " << std::get<3>(ev) << ")" << std::endl;

		if (std::get<3>(ev) < 0.0) {
			if (std::get<2>(ev) == -1) {
				device.freeCPU();
				resourcesUsed--;
				popReadyQueue(std::get<0>(ev));
			} 
			if (std::get<2>(ev) >= 0) {
				if (taskResponseTimes.at(std::get<1>(ev)) == -1.0) {
					taskResponseTimes.at(std::get<1>(ev)) = std::get<0>(ev);
				}
				resourcesUsed--;
				popIOQueue(-std::get<2>(ev), std::get<0>(ev));
			}
			continue;
		}

		// if (std::get<2>(ev) == -100) {
		// 	std::cout << std::get<0>(ev) << "ms" << " - " << 
		// 		"Task " << std::get<1>(ev) << ": "  << 
		// 		"(Dev: " << std::get<2>(ev) << ", Dur: " << std::get<3>(ev) << ")" << std::endl;
		// }

		// New CPU Task
		if (std::get<2>(ev) == -1) {
			pushReadyQueue(ev);
		}
		// New IO Task
		if (std::get<2>(ev) >= 0) {
			pushIOQueue(0, ev);
		}
		// Start Task
		if (std::get<2>(ev) == -100) {
			auto currentTime = std::get<0>(ev);
			completeStep(ev, currentTime);
		}

	}

	// std::cout << "-------------------------------" << std::endl;
	// printQueue();

}

void EventQueue::pushReadyQueue(step item) {
	rqueue->push(item);

	if (device.getNumCPUs() > 0) {
		popReadyQueue(std::get<0>(item));
		return;
	}

	// std::cout << "	Task " << std::get<1>(item) << " waiting for free CPU. Time: " << std::get<0>(item) << std::endl;

	return;
}

void EventQueue::popReadyQueue(double currentTime) {
	auto item = rqueue->pop();

	// If Queue is empty
	if (std::get<1>(item) == -1) { return; }

	device.useCPU();
	resourcesUsed++;
	events.push(std::make_tuple(
		currentTime + std::get<3>(item) + contextSwitchCost,
		std::get<1>(item),
		-1,
		-1.0
	));
	completeStep(item, currentTime);
	return;
}

void EventQueue::pushIOQueue(int id, step item) {
	device.pushIO(id, item);
	resourcesUsed++;

	if (device.getIOSize(id) == 1) {
		popIOQueue(id, std::get<0>(item));
		return;
	}

	// std::cout << "	Task " << std::get<1>(item) << " waiting for IO Device " << id << ". Time: " << std::get<0>(item) << std::endl;

	return;
}

void EventQueue::popIOQueue(int id, double currentTime) {
	auto item = device.popIO(id);

	// If Queue is empty
	if (std::get<1>(item) == -1) { return; }

	// std::cout << "There are " << device.getIOSize(id) << " steps waiting on IO Device " << id << "." << std::endl;
	events.push(std::make_tuple(
		currentTime + std::get<3>(item) + contextSwitchCost,
		std::get<1>(item),
		-id,
		-1.0
	));
	completeStep(item, currentTime);
	return;
}

void EventQueue::completeStep(step item, double currentTime) {

	// Retrieve the next event.
	if (allTasks[std::get<1>(item)].size() == 0) { return; }
	auto nextTask = allTasks[std::get<1>(item)].pop();

	events.push(std::make_tuple(
		currentTime + (currentTime - std::get<0>(item)) + std::get<3>(item) + contextSwitchCost, 
		std::get<1>(item),
		std::get<0>(nextTask),
		std::get<1>(nextTask)
	));

	return;
}

void EventQueue::computeLatency() {

	for (unsigned int i = 0; i < taskStartTimes.size(); ++i) {
		latency.push_back(taskFinishTimes[i] - taskStartTimes[i]);
	}

	return;
}

void EventQueue::printLatency() {

	computeLatency();
	// for (unsigned int i = 0; i < latency.size(); ++i) {
	// 	std::cout << "Task " << i << " took " << latency[i] << " time units to finish. " << std::endl;
	// }
	CandleStats latencyStats(latency);

	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "Latency Statistics:" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "Mean Latency: " << latencyStats.getMean() << std::endl;
	std::cout << "Minimum Latency:" << *std::min_element(latency.begin(), latency.end()) << std::endl;
	if ((*std::min_element(latency.begin(), latency.end())) <= 0.0) { std::cout << " (Some tasks did not respond) " << std::endl;}
	std::cout << "Maximum Latency: " << *std::max_element(latency.begin(), latency.end()) << std::endl;
	std::cout << "Latency Std. Dev.: " << latencyStats.getStandardDeviation() << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << std::endl << std::endl;

	return;
}

void EventQueue::printThroughput() {

	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "Throughput Statistics:" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "Computed " << taskStartTimes.size() << " tasks in " << runningTime << " time units." << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << std::endl << std::endl;

	return;
}

void EventQueue::printResponseTimes() {

	CandleStats ResponseStats(taskResponseTimes);

	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "Response Time Statistics:" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "Mean Response Time: " << ResponseStats.getMean() << std::endl;
	std::cout << "Minimum Response Time: " << *std::min_element(taskResponseTimes.begin(), taskResponseTimes.end()) << std::endl;
	std::cout << "Maximum Response Time: " << *std::max_element(taskResponseTimes.begin(), taskResponseTimes.end()) << std::endl;
	std::cout << "Response Time Std. Dev.: " << ResponseStats.getStandardDeviation() << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << std::endl << std::endl;

	return;
}

void EventQueue::calculateUtilization() {

	utilization.push_back(resourcesUsed / totalResources);

	return;
}

void EventQueue::printUtilization() {

	// for (unsigned int i = 0; i < latency.size(); ++i) {
	// 	std::cout << "Task " << i << " took " << latency[i] << " time units to finish. " << std::endl;
	// }
	CandleStats utilizationStats(utilization);

	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "Utilization Statistics:" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << "Mean Utilization: " << utilizationStats.getMean() * 100 << "%" << std::endl;
	std::cout << "Minimum Utilization:" << *std::min_element(utilization.begin(), utilization.end()) * 100 << "%" << std::endl;
	std::cout << "Maximum Utilization: " << *std::max_element(utilization.begin(), utilization.end()) * 100 << "%" << std::endl;
	std::cout << "Utilization Std. Dev.: " << utilizationStats.getStandardDeviation() * 100 << "%" << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << std::endl << std::endl;

	return;
}

void EventQueue::printQueue() {

	for (unsigned int i = 0; i < events.size(); ++i) {
		auto e = events.top();
		events.pop();
		std::cout << std::get<0>(e) << "ms" << " - " << 
			"Task " << std::get<1>(e) << ": "  << 
			"(Dev: " << std::get<2>(e) << ", Dur: " << std::get<3>(e) << ")" << std::endl;
	}

	
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

