// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// FIFO Ready Queue Implementation

#include "FIFOQueue.hpp"

void FIFOQueue::push(Event item) {
	rqueue.push(item);
}

Event FIFOQueue::pop() {
	// Return Dummy Event
	if (rqueue.empty()) { return Event(); }

	auto item = rqueue.front();
	rqueue.pop();

	return item;
}
