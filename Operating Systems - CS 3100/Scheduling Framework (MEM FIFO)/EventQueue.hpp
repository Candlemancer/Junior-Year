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
#include "Event.hpp"

// <Event Time, Task, Device, Running Time>
// typedef std::tuple<double, int, int, double> step;

class EventQueue {
public:
	// Constructors
	EventQueue(
		double frequency, 
		double mixRate, 
		double contextCost, 
		int numCPUs, 
		int numIOs, 
		int algorithm,
		double quantumSize
	);

	// Member Functions
	void generateTasks(double frequency, double mixRate, int numIOs);
	void update();
	void pushReadyQueue(Event item);
	void popReadyQueue(double currentTime);
	void pushIOQueue(Event item);
	void popIOQueue(int id, double currentTime);
	void completeStep(Event item);

	// Statistics
	void computeThroughput();
	void printThroughput();
	void computeLatency();
	void printLatency();
	void computeResponseTimes();
	void printResponseTimes();
	void computeUtilization();
	void printUtilization();

	// DebugFunctions
	void printEvent(Event item);
	void printStartTimes();
	void printFinishTimes();


private:
	// Member Data
	double contextSwitchCost;
	double const runningTime = 10000.0;
	int resourcesUsed;
	int totalResources;

	std::priority_queue<Event, std::vector<Event>, std::greater<Event>> events;
	std::vector<Task> allTasks;
	Device device;
	std::unique_ptr<ReadyQueue> rqueue;

	// Raw Time Data
	std::vector<double> taskStartTimes;
	std::vector<double> taskResponseTimes;
	std::vector<double> taskFinishTimes;

	// Groomed Time Data
	int throughput;
	std::vector<double> latency;
	std::vector<double> responses;
	std::vector<double> utilization;

};

#endif
