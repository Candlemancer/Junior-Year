// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// Shortest Job First Queue Header

#ifndef SHORTEST_JOB_QUEUE_HPP
#define SHORTEST_JOB_QUEUE_HPP

#include "ReadyQueue.hpp"

#include <functional>
#include <queue>
#include <tuple>

#include "Event.hpp"

// typedef std::tuple<double, int, int, double> step;

class ShortestJobQueue : public ReadyQueue {
public:
	// Constructors
	ShortestJobQueue();

	// Member Functions
	void push(Event item);
	Event pop();

	// void setQuantum(int newQuantum) { quantumSize = newQuantum; return; }
	// int getQuantum() { return quantumSize; }
	
private:
	// Member Data
	// std::function<bool(Event, Event)> compareTimeRemaining = 
		// [](Event a, Event b) -> bool{ (std::get<3>(a) > std::get<3>(b)) ? return true : return false; };
	std::priority_queue<
		Event, 
		std::vector<Event>,  
		std::function<bool(Event, Event)>
	> rqueue;
	// int quantumSize;
	// int lastTaskRun;

	
};

#endif
