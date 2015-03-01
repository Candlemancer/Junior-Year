// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// Event Queue Header

#ifndef EVENT_QUEUE_HPP
#define EVENT_QUEUE_HPP

#include <queue>
#include <vector>
#include <string>
#include <memory>
#include "Task.hpp"
#include "Device.hpp"
#include "ReadyQueue.hpp"

typedef std::tuple<double, int, int, double> step;

class EventQueue {
public:
	// Constructors
	EventQueue(int numTasks = 1);

	// Member Functions
	void update();
	void pushReadyQueue(step item);
	void popReadyQueue(double currentTime);
	void pushIOQueue(int id, step item);
	void popIOQueue(int id, double currentTime);
	void completeStep(step item, double currentTime);
	void printQueue();
private:
	// Member Data
	std::priority_queue<step, std::vector<step>, std::greater<step>> events;
	std::vector<Task> allTasks;
	Device device;
	std::unique_ptr<ReadyQueue> rqueue;

};

#endif
