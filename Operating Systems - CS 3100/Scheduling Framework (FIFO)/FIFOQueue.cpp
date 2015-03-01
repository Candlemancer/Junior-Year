// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// FIFO Ready Queue Implementation

#include "FIFOQueue.hpp"

void FIFOQueue::push(step item) {
	rqueue.push(item);
}

step FIFOQueue::pop() {
	auto item = rqueue.front();
	rqueue.pop();

	return item;
}
