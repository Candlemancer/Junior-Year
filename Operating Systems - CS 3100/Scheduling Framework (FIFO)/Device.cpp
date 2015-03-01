// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// Device Class Implementation

#include "Device.hpp"

#include <algorithm>

Device::Device(unsigned int numCPUs, unsigned int numIOs) :
	cpuCount(numCPUs) {

	// for (unsigned int i = 0; i < numIOs; ++i) {
	// 	ioDevices.push_back(std::queue<double>());	
	// }
	std::generate_n(back_inserter(ioDevices), numIOs, [](){ return std::queue<double>(); });

	return;
}
