// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// Round Robin Ready Queue Header

#ifndef ROUND_ROBIN_QUEUE_HPP
#define ROUND_ROBIN_QUEUE_HPP

#include "ReadyQueue.hpp"

#include <map>
#include <queue>
#include <tuple>

#include "Event.hpp"

// typedef std::tuple<double, int, int, double> step;

class RoundRobinQueue : public ReadyQueue {
public:
	// Constructors
	RoundRobinQueue(int initQuantum = 20.0);

	// Member Functions
	void push(Event item);
	Event pop();

	void setQuantum(double newQuantum) { quantumSize = newQuantum; return; }
	int getQuantum() { return quantumSize; }
	
private:
	// Member Data
	std::map<int, std::queue<Event>> rqueue;
	double quantumSize;
	int lastTaskRun;

	
};

#endif
