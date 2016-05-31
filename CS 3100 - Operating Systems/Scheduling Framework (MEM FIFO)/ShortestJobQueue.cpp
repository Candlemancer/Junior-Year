// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// Shortest Job First Implementation

#include "ShortestJobQueue.hpp"
#include <iostream>

ShortestJobQueue::ShortestJobQueue() :
	rqueue (
		[](Event a, Event b) -> bool { if (a.m_duration > b.m_duration) return true; return false; }
	)
	{}

void ShortestJobQueue::push(Event item) {
	rqueue.push(item);

	return;
}

Event ShortestJobQueue::pop() {

	// If queue is empty, return dummy event
	if (rqueue.empty()) { return Event(); }

	auto item = rqueue.top();
	rqueue.pop();

	return item;
}
