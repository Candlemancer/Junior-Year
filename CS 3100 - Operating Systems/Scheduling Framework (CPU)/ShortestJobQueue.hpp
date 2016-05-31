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

typedef std::tuple<double, int, int, double> step;

class ShortestJobQueue : public ReadyQueue {
public:
	// Constructors
	ShortestJobQueue();

	// Member Functions
	void push(step item);
	step pop();

	// void setQuantum(int newQuantum) { quantumSize = newQuantum; return; }
	// int getQuantum() { return quantumSize; }
	
private:
	// Member Data
	// std::function<bool(step, step)> compareTimeRemaining = 
		// [](step a, step b) -> bool{ (std::get<3>(a) > std::get<3>(b)) ? return true : return false; };
	std::priority_queue<
		step, 
		std::vector<step>,  
		std::function<bool(step, step)>
	> rqueue;
	// int quantumSize;
	// int lastTaskRun;

	
};

#endif
