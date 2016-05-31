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
	EventQueue(double frequency, double mixRate, double contextCost, int numCPUs, int numIOs);

	// Member Functions
	void generateTasks(double frequency, double mixRate, int numIOs);
	void update();
	void pushReadyQueue(step item);
	void popReadyQueue(double currentTime);
	void pushIOQueue(int id, step item);
	void popIOQueue(int id, double currentTime);
	void completeStep(step item, double currentTime);

	void computeLatency();
	void printLatency();
	void printResponseTimes();
	void printThroughput();
	void calculateUtilization();
	void printUtilization();

	void printQueue();
	void printStartTimes();
	void printFinishTimes();


private:
	// Member Data
	double contextSwitchCost;
	double const runningTime = 10000.0;
	int resourcesUsed;
	int totalResources;

	std::priority_queue<step, std::vector<step>, std::greater<step>> events;
	std::vector<Task> allTasks;
	Device device;
	std::unique_ptr<ReadyQueue> rqueue;

	std::vector<double> taskStartTimes;
	std::vector<double> taskResponseTimes;
	std::vector<double> taskFinishTimes;

	std::vector<double> latency;
	std::vector<double> utilization;

};

#endif
