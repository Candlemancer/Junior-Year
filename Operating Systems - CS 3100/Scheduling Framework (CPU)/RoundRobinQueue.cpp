// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// Round Robin Ready Queue Implementation

#include "RoundRobinQueue.hpp"

RoundRobinQueue::RoundRobinQueue(int initNumTasks) :
	numTasks(initNumTasks) {
		
	}

void RoundRobinQueue::push(step item);
step RoundRobinQueue::pop();
