// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// Shortest Job First Implementation

#include "ShortestJobQueue.hpp"
#include <iostream>

ShortestJobQueue::ShortestJobQueue() :
	rqueue (
		// Careful, this if statement is missing its {}'s.
		[](step a, step b) -> bool {if (std::get<3>(a) > std::get<3>(b)) return true; return false;}
	)
	{}

void ShortestJobQueue::push(step item) {
	rqueue.push(item);

	return;
}

step ShortestJobQueue::pop() {

	// If queue is empty, return dummy event
	if (rqueue.empty()) { return std::make_tuple(0.0, -1, -1, 0.0); }

	auto item = rqueue.top();
	rqueue.pop();

	return item;
}
