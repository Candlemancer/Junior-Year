// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// Device Class Implementation

#include "Device.hpp"

#include <algorithm>

Device::Device(unsigned int numCPUs, unsigned int numIOs) :
	cpuCount(numCPUs) {

	std::generate_n(back_inserter(ioDevices), numIOs, [](){ return std::queue<Event>(); });

	return;
}

void Device::pushIO(int id, Event item) { 
	ioDevices[id].push(item); 

	return; 
}

Event Device::popIO(int id) { 
	if (ioDevices[id].empty()) { return Event(Event::NO_OP, 0.0, 0.0, -1, id); }
	auto item = ioDevices[id].front(); 
	ioDevices[id].pop(); 
	return item;
}
