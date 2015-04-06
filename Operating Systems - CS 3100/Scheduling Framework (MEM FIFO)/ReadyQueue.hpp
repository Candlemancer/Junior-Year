// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// Ready Queue Interface

#ifndef READY_QUEUE_HPP
#define READY_QUEUE_HPP

#include <tuple>

#include "Event.hpp"

// typedef std::tuple<double, int, int, double> step;

class ReadyQueue 
{
public:
	// Member Functions
	void virtual push(Event item) = 0;
	Event virtual pop() = 0;

private:
	// Member Data
	
};

#endif
