// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// FIFO Ready Queue Implementation

#include "FIFOQueue.hpp"

void FIFOQueue::push(step item) {
	rqueue.push(item);
}

step FIFOQueue::pop() {
	if (rqueue.empty()) { return std::make_tuple(0.0, -1, -1, 0.0); }

	auto item = rqueue.front();
	rqueue.pop();

	return item;
}
