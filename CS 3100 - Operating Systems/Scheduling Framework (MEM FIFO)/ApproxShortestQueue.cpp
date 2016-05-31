// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// Approximate Shortest Job First Implementation

#include "ApproxShortestQueue.hpp"
#include <iostream>

ApproxShortestQueue::ApproxShortestQueue() :
	rqueue (
		// Comparison Function for priority queue. Items with lower average runtimes are given
		// higher priority.
		[&](Event a, Event b) -> bool {
			if (std::get<0>(avgTimes[a.m_taskNumber]) / std::get<1>(avgTimes[a.m_taskNumber]) > 
				std::get<0>(avgTimes[b.m_taskNumber]) / std::get<1>(avgTimes[b.m_taskNumber]) ) {
				return true; 
			} 
			return false;
		}
	)
	{}

void ApproxShortestQueue::push(Event item) {

	// Create a new entry in the avgTimes map if needed.
	avgTimes.emplace(item.m_taskNumber, std::pair<double, double>(0.0, 0.0));

	// Update the values of the entry
	std::get<0>(avgTimes[item.m_taskNumber]) += item.m_duration;
	std::get<1>(avgTimes[item.m_taskNumber]) += 1.0;

	rqueue.push(item);

	return;
}

Event ApproxShortestQueue::pop() {

	// If queue is empty, return dummy event
	if (rqueue.empty()) { return Event(); }

	auto item = rqueue.top();
	rqueue.pop();

	return item;
}
