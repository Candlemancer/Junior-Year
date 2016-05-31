// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// FIFO Ready Queue Header

#ifndef FIFO_QUEUE_HPP
#define FIFO_QUEUE_HPP

#include "ReadyQueue.hpp"

#include <queue>
#include <tuple>

typedef std::tuple<double, int, int, double> step;

class FIFOQueue : public ReadyQueue {
public:
	// Constructors
	// FIFOQueue();

	// Member Functions
	void push(step item);
	step pop();
	
private:
	// Member Data
	std::queue<step> rqueue;

};

#endif
