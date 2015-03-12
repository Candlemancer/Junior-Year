// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// Driver Code

#include <iostream>

#include "Task.hpp"
#include "Device.hpp"
#include "EventQueue.hpp"


int main() {

	auto numCPUs = 2;
	auto numIOs = 3;
	auto contextSwitchCost = 1.0;
	auto taskMixRate = 0.5;
	auto taskCreationFrequency = 100.0;

	char choice = '!';
	auto retry = true;

	while(retry) {
		std::cout << std::endl;	
		std::cout << "================================================================================" << std::endl;
		std::cout << "Welcome to the Scheduling Framework Application. What Would you Like to do?" << std::endl;
		std::cout << "'R' - Run the Simulation" << std::endl;
		std::cout << "'C' - Change the number of CPU's on the device" << std::endl;
		std::cout << "'I' - Change the number of IO Devices on the device" << std::endl;
		std::cout << "'S' - Change the cost of a context switch" << std::endl;
		std::cout << "'M' - Change the amount of CPU bound vs IO bound tasks" << std::endl;
		std::cout << "'F' - Change the task creation frequency" << std::endl;
		std::cout << "'Q' - Quit" << std::endl;
		std::cout << "================================================================================" << std::endl;
		while (!(std::cin >> choice)) {
			std::cout << "I'm sorry, I didn't understand that. Please try again." << std::endl;
			std::cin.clear();
			std::cin.ignore(4000000000, '\n');
		}

		switch(choice) {
			case 'R':
			case 'r':
				break;

			case 'C':
			case 'c':
				std::cout << "Please input the new number of CPUs [1, MAXINT]: " << std::endl;
				std::cin >> numCPUs;
				continue;
				break;

			case 'I':
			case 'i':			
				std::cout << "Please input the new number of IO devices [1, MAXINT]: " << std::endl;
				std::cin >> numIOs;
				continue;
				break;	

			case 'S':
			case 's':		
				std::cout << "Please input the new cost of a context switch [0.0 - 9999.0: " << std::endl;
				std::cin >> contextSwitchCost;
				continue;
				break;	

			case 'M':
			case 'm':
				std::cout << "Please input the new rate of IO bound tasks. (CPU bound " << std::endl;
				std::cout << "tasks will be the complement of this value) [0.0 - 1.0]: " << std::endl;
				std::cin >> taskMixRate;
				continue;
				break;	

			case 'F':
			case 'f':
				std::cout << "Please input the new frequency of task creation. [1.0 - 9999.0]: " << std::endl;
				std::cin >> taskCreationFrequency;

				continue;
				break;	

			case 'Q':
			case 'q':
				std::cout << "All right, have a good day!" << std::endl;
				return 0;
				break;

			default:
				std::cout << "Sorry, I didn't understand that. Try again." << std::endl;
				continue;
				break;	
		}

		EventQueue myEventQueue(
			taskCreationFrequency, 
			taskMixRate,
			contextSwitchCost,
			numCPUs,
			numIOs);

		// myEventQueue.printStartTimes();
		// myEventQueue.printFinishTimes();
		myEventQueue.printThroughput();
		myEventQueue.printLatency();
		myEventQueue.printResponseTimes();
		myEventQueue.printUtilization();


	}



	return 0;
}
