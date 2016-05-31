// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// Approximate Shortest Job First Implementation

#include "ApproxShortestQueue.hpp"
#include <iostream>

ApproxShortestQueue::ApproxShortestQueue() :
	rqueue (
		// Careful, this if statement is missing its {}'s.
		[&](step a, step b) -> bool {
			if (std::get<0>(avgTimes[std::get<1>(a)]) / std::get<1>(avgTimes[std::get<1>(a)]) > 
				std::get<0>(avgTimes[std::get<1>(b)]) / std::get<1>(avgTimes[std::get<1>(b)]) ) {
				return true; 
			} 
			return false;
		}
	)
	{}

void ApproxShortestQueue::push(step item) {

	avgTimes.emplace(std::get<1>(item), std::pair<double, double>(0.0, 0.0));

	std::get<0>(avgTimes[std::get<1>(item)]) += std::get<3>(item);
	std::get<1>(avgTimes[std::get<1>(item)]) += 1.0;
	// std::get<2>(avgTimes[std::get<1>(item)]) = 
		// std::get<0>(avgTimes[std::get<1>(item)]) / std::get<1>(avgTimes[std::get<1>(item)]);

	rqueue.push(item);

	return;
}

step ApproxShortestQueue::pop() {

	// If queue is empty, return dummy event
	if (rqueue.empty()) { return std::make_tuple(0.0, -1, -1, 0.0); }

	auto item = rqueue.top();
	rqueue.pop();

	return item;
}
