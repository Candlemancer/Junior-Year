// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// Round Robin Ready Queue Header

#ifndef ROUND_ROBIN_QUEUE_HPP
#define ROUND_ROBIN_QUEUE_HPP

#include "ReadyQueue.hpp"

#include <unordered_map>
#include <queue>
#include <tuple>

typedef std::tuple<double, int, int, double> step;

class RoundRobinQueue : public ReadyQueue {
public:
	// Constructors
	RoundRobinQueue(dtNumTasks);

	// Member Functions
	void push(step item);
	step pop();

	void increaseTasks();
	void decreaseTasks();
	
private:
	// Member Data
	std::unordered_map<int, std::queue<step>> rqueue;
	// int ;

	
};

#endif
