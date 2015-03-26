// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// Round Robin Ready Queue Implementation

#include "RoundRobinQueue.hpp"
#include <iostream>
#include <utility>

RoundRobinQueue::RoundRobinQueue(int initQuantum) :
	quantumSize(initQuantum),
	lastTaskRun(-1) {}

void RoundRobinQueue::push(step item) {

	// Either find the existing index or create a new one.
	rqueue.emplace(std::get<1>(item), std::queue<step>());

	// Split the job into quantum chunks.
	while (std::get<3>(item) > quantumSize) {
		rqueue[std::get<1>(item)].push(std::make_tuple(
			std::get<0>(item),
			std::get<1>(item),
			std::get<2>(item),
			quantumSize
		));

		// std::cout << std::get<0>(item) << "ms" << " - " << 
		// 	"Task " << std::get<1>(item) << ": "  << 
		// 	"(Dev: " << std::get<2>(item) << ", Dur: " << std::get<3>(item) << ")" << std::endl;

		std::get<0>(item) += quantumSize;
		std::get<3>(item) -= quantumSize;
	}

	rqueue[std::get<1>(item)].push(std::make_tuple(
		std::get<0>(item),
		std::get<1>(item),
		std::get<2>(item),
		std::get<3>(item)
	));

	// std::cout << std::get<0>(item) << "ms" << " - " << 
	// 	"Task " << std::get<1>(item) << ": "  << 
	// 	"(Dev: " << std::get<2>(item) << ", Dur: " << std::get<3>(item) << ")" << std::endl;

}

step RoundRobinQueue::pop() {

	// If queue is empty, return
	if (rqueue.empty()) { return std::make_tuple(0.0, -1, -1, 0.0); }

	// Increment the map iterator
	auto mapIterator = rqueue.begin();
	if (lastTaskRun != -1) { mapIterator = rqueue.find(lastTaskRun); }
	if (mapIterator != rqueue.end()) { mapIterator++; } 
	if (mapIterator == rqueue.end()) { mapIterator = rqueue.begin(); }

	if ((*mapIterator).second.empty()) { return std::make_tuple(0.0, -1, -1, 0.0); }
	auto item = (*mapIterator).second.front();
	(*mapIterator).second.pop();

	if (std::get<3>(item) < quantumSize) { rqueue.erase(mapIterator); }
	return item;
}

