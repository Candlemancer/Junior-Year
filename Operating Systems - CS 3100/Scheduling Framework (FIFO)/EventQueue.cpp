// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// Event Queue Implementation

#include "EventQueue.hpp"

#include <algorithm>
#include <iostream>

#include "FIFOQueue.hpp"

EventQueue::EventQueue(int numTasks) {
	std::generate_n(back_inserter(allTasks), numTasks, [](){ return Task(); });

	std::cout << "==============================================" << std::endl;
	std::cout << "Generated the following Tasks:" << std::endl;
	for (auto&& i : allTasks){
		std::cout << "Task with " << i.getTasks().size() << " steps." << std::endl;
	}
	std::cout << "==============================================" << std::endl;
	
	for (unsigned int i = 0; i < allTasks.size(); ++i) {
		events.push(std::make_tuple(0.0, i, -100, 0.1));
	}
	

	rqueue = std::unique_ptr<ReadyQueue>(new FIFOQueue());
	update();
	
}

void EventQueue::update() {

	auto totalTasks = 0u;
	for (auto&& tl : allTasks){
		totalTasks += tl.size();
	}
	
	// std::cout << totalTasks << std::endl;
	// std::cout << "--------------------" << std::endl;

	for (unsigned int i = 0; i < totalTasks; ++i) {
	
		// Read the top event
		auto ev = events.top();
		events.pop();

		// std::cout << std::get<0>(ev) << "ms" << " - " << 
		// 	"Task " << std::get<1>(ev) << ": "  << 
		// 	"(Dev: " << std::get<2>(ev) << ", Dur: " << std::get<3>(ev) << ")" << std::endl;

		if (std::get<3>(ev) < 0.0) {
			if (std::get<2>(ev) == -1) {
				device.freeCPU();
				popReadyQueue(std::get<0>(ev));
			} 
			if (std::get<2>(ev) >= 0) {
				popIOQueue(-std::get<2>(ev), std::get<0>(ev));
			}
			totalTasks++;
			continue;
		}

		std::cout << std::get<0>(ev) << "ms" << " - " << 
			"Task " << std::get<1>(ev) << ": "  << 
			"(Dev: " << std::get<2>(ev) << ", Dur: " << std::get<3>(ev) << ")" << std::endl;

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

	std::cout << std::get<0>(events.top()) << "ms" << " - " << 
	"Task " << std::get<1>(events.top()) << ": "  << 
	"(Dev: " << std::get<2>(events.top()) << ", Dur: " << std::get<3>(events.top()) << ")" << std::endl;

}

void EventQueue::pushReadyQueue(step item) {
	rqueue->push(item);

	if (device.getNumCPUs() > 0) {
		popReadyQueue(std::get<0>(item));
		return;
	}

	std::cout << "	Task " << std::get<1>(item) << " waiting for free CPU. Time: " << std::get<0>(item) << std::endl;

	return;
}

void EventQueue::popReadyQueue(double currentTime) {
	auto item = rqueue->pop();

	// If Queue is empty
	if (std::get<1>(item) == -1) { return; }

	device.useCPU();
	events.push(std::make_tuple(
		currentTime + std::get<3>(item),
		std::get<1>(item),
		-1,
		-1.0
	));
	completeStep(item, currentTime);
	return;
}

void EventQueue::pushIOQueue(int id, step item) {
	device.pushIO(id, item);

	if (device.getIOSize(id) == 1) {
		events.push(std::make_tuple(
			std::get<0>(item) + std::get<3>(item),
			std::get<1>(item),
			-id,
			-1.0
		));
		return;
	}

	std::cout << "	Task " << std::get<1>(item) << " waiting for IO Device " << id << ". Time: " << std::get<0>(item) << std::endl;

	return;
}

void EventQueue::popIOQueue(int id, double currentTime) {
	auto item = device.popIO(id);

	// If Queue is empty
	if (std::get<1>(item) == -1) { return; }

	// std::cout << "There are " << device.getIOSize(id) << " steps waiting on IO Device " << id << "." << std::endl;
	events.push(std::make_tuple(
		currentTime + std::get<3>(item),
		std::get<1>(item),
		-id,
		-1.0
	));
	completeStep(item, currentTime);
	return;
}

void EventQueue::completeStep(step item, double currentTime) {

	// Retrieve the next event.
	auto nextTask = allTasks[std::get<1>(item)].pop();

	// if (std::get<2>(item) == -1) {
	// 	popReadyQueue(currentTime);
	// }
	// if (std::get<2>(item) >= 0) {
	// 	popIOQueue(std::get<2>(item), currentTime);
	// }

	events.push(std::make_tuple(
		currentTime + (currentTime - std::get<0>(item)) + std::get<3>(item), 
		std::get<1>(item),
		std::get<0>(nextTask),
		std::get<1>(nextTask)
	));

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
