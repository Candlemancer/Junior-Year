// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// Approximate Shortest Job First Queue Header

#ifndef APPROX_SHORTEST_QUEUE_HPP
#define APPROX_SHORTEST_QUEUE_HPP

#include "ReadyQueue.hpp"

#include <functional>
#include <utility>
#include <queue>
#include <tuple>
#include <map>

#include "Event.hpp"

// typedef std::tuple<double, int, int, double> step;

class ApproxShortestQueue : public ReadyQueue {
public:
	// Constructors
	ApproxShortestQueue();

	// Member Functions
	void push(Event item);
	Event pop();
	
private:
	// Member Data
	std::priority_queue<
		Event, 
		std::vector<Event>,  
		std::function<bool(Event, Event)>
	> rqueue;
	
	std::map<int, std::pair<double, double>> avgTimes;	
	
};

#endif
