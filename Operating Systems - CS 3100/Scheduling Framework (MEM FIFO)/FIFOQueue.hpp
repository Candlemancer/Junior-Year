// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// FIFO Ready Queue Header

#ifndef FIFO_QUEUE_HPP
#define FIFO_QUEUE_HPP

#include "ReadyQueue.hpp"

#include <queue>
#include <tuple>

#include "Event.hpp"

// typedef std::tuple<double, int, int, double> step;

class FIFOQueue : public ReadyQueue {
public:
	// Constructors
	// FIFOQueue();

	// Member Functions
	void push(Event item);
	Event pop();
	
private:
	// Member Data
	std::queue<Event> rqueue;

};

#endif
