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
	

	events.push(std::make_tuple(0.0, 0, -100, 0.0));
	events.push(std::make_tuple(0.0, 1, -100, 0.0));

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

		std::cout << std::get<0>(ev) << "ms" << " - " << 
			"Task " << std::get<1>(ev) << ": "  << 
			"(Dev: " << std::get<2>(ev) << ", Dur: " << std::get<3>(ev) << ")" << std::endl;

		auto currentTime = std::get<0>(ev);
		auto currentTask = allTasks[std::get<1>(ev)].pop();

		// Handle Accordingly
		events.push(std::make_tuple(
			currentTime + std::get<1>(currentTask), 
			std::get<1>(ev),
			std::get<0>(currentTask),
			std::get<1>(currentTask)
		));

	}

}

void EventQueue::pushReadyQueue(step item) {
	rqueue->push(item);

	return;
}

step EventQueue::popReadyQueue() {
	auto item = rqueue->pop();

	return item;
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
