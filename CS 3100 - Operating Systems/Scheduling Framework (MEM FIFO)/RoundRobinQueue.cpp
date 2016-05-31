// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// Round Robin Ready Queue Implementation

#include "RoundRobinQueue.hpp"
#include <algorithm>
#include <iostream>
#include <utility>

RoundRobinQueue::RoundRobinQueue(int initQuantum) :
	quantumSize(initQuantum),
	lastTaskRun(-1) {}

void RoundRobinQueue::push(Event item) {

	// Either find the existing index or create a new one.
	rqueue.emplace(item.m_taskNumber, std::queue<Event>());

	// Split the job into quantum chunks.
	for (unsigned int i = 0; (item.m_duration - i * quantumSize) > 0; i++) {
		rqueue[item.m_taskNumber].push(

			Event(
				Event::CPU_START,
				item.m_startTime + quantumSize * i,
				std::min(item.m_duration - quantumSize * i, quantumSize),
				item.m_taskNumber
			)

			// std::make_tuple(
			// std::get<0>(item),
			// item.m_taskNumber,
			// std::get<2>(item),
			// quantumSize
		);

		// std::cout << std::get<0>(item) << "ms" << " - " << 
		// 	"Task " << item.m_taskNumber << ": "  << 
		// 	"(Dev: " << std::get<2>(item) << ", Dur: " << item.m_duration << ")" << std::endl;

		// std::get<0>(item) += quantumSize;
		// item.m_duration -= quantumSize;
	}

	// rqueue[item.m_taskNumber].push(

	// 	Event(

	// 	)


	// 	std::make_tuple(
	// 	std::get<0>(item),
	// 	item.m_taskNumber,
	// 	std::get<2>(item),
	// 	item.m_duration
	// ));

	// std::cout << std::get<0>(item) << "ms" << " - " << 
	// 	"Task " << item.m_taskNumber << ": "  << 
	// 	"(Dev: " << std::get<2>(item) << ", Dur: " << item.m_duration << ")" << std::endl;

}

Event RoundRobinQueue::pop() {

	// If queue is empty, return
	if (rqueue.empty()) { return Event(); }

	// Increment the map iterator
	auto mapIterator = rqueue.begin();
	if (lastTaskRun != -1) { mapIterator = rqueue.find(lastTaskRun); }
	if (mapIterator != rqueue.end()) { mapIterator++; } 
	if (mapIterator == rqueue.end()) { mapIterator = rqueue.begin(); }

	if ((*mapIterator).second.empty()) { return Event(); }
	auto item = (*mapIterator).second.front();
	(*mapIterator).second.pop();

	if (item.m_duration < quantumSize) { rqueue.erase(mapIterator); }
	return item;
}

