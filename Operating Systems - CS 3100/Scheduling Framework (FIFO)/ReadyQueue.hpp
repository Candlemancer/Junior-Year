// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// Ready Queue Interface

#ifndef READY_QUEUE_HPP
#define READY_QUEUE_HPP

#include <tuple>

typedef std::tuple<double, int, int, double> step;

class ReadyQueue 
{
public:
	// Member Functions
	void virtual push(step item) = 0;
	step virtual pop() = 0;

private:
	// Member Data
	
};

#endif
