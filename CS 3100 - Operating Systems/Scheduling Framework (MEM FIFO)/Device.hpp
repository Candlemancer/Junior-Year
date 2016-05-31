// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// Device Class Header

#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <queue>
#include <tuple>
#include <vector>

#include "Event.hpp"

// typedef std::tuple<double, int, int, double> step;

class Device {
public:
	// Constructors
	Device(unsigned int numCPUs = 1, unsigned int numIOs = 1);

	// Member Functions
	int getNumCPUs() { return cpuCount; }
	int getNumIOs() { return ioDevices.size(); } 
	int getIOSize(int id) { return ioDevices[id].size(); }
	void useCPU() { cpuCount--; return; }
	void freeCPU() { cpuCount++; return; }
	void pushIO(int id, Event item);
	Event popIO(int id);


private:
	// Member Data
	int cpuCount;

	std::vector<std::queue<Event>> ioDevices;
};

#endif
