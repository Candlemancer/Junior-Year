// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// Device Class Header

#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <queue>
#include <vector>

class Device {
public:
	// Constructors
	Device(unsigned int numCPUs = 1, unsigned int numIOs = 1);

	// Member Functions
	int getNumCPUs() {return cpuCount;}
	int getNumIOs() {return ioDevices.size();}
	void useCPU() { cpuCount--; return; }
	void freeCPU() { cpuCount++; return; }


private:
	// Member Data
	int cpuCount;

	std::vector<std::queue<double>> ioDevices;
};

#endif
