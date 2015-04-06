// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// Driver Code

#include <iostream>

#include "Task.hpp"
#include "Device.hpp"
#include "EventQueue.hpp"


int main() {

	auto algorithm = 1;
	auto quantumSize = 20.0;
	auto numCPUs = 1;
	auto numIOs = 2;
	auto numPages = 50;
	auto contextSwitchCost = 1.0;
	auto pageFaultCost = 10.0;
	auto taskMixRate = 0.5;
	auto taskCreationFrequency = 100.0;

	char choice = '!';
	auto retry = true;

	while(retry) {
		std::cout << std::endl;	
		std::cout << "================================================================================" << std::endl;
		std::cout << "Welcome to the Scheduling Framework Application. What Would you Like to do?" << std::endl;
		std::cout << "'R' - Run the Simulation" << std::endl;
		std::cout << "'A' - Change the algorithm used for CPU scheduling" << std::endl;
		std::cout << "'C' - Change the number of CPU's on the device" << std::endl;
		std::cout << "'I' - Change the number of IO Devices on the device" << std::endl;
		std::cout << "'M' - Change the number of memory pages on the device" << std::endl;
		std::cout << "'S' - Change the cost of a context switch" << std::endl;
		std::cout << "'P' - Change the cost of a page fault" << std::endl;
		std::cout << "'K' - Change the quantum size of the round-robin ready queue" << std::endl;
		std::cout << "'B' - Change the balance of CPU bound vs IO bound tasks" << std::endl;
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

			case 'A':
			case 'a':
				std::cout << "--------------------------------------------------------------------------------" << std::endl;
				std::cout << "'1' - FIFO Ready Queue" << std::endl;
				std::cout << "'2' - Round Robin Ready Queue" << std::endl;
				std::cout << "'3' - Shortest Job First Ready Queue" << std::endl;
				std::cout << "'4' - Approximate Shortest Job First Ready Queue" << std::endl;
				std::cout << "--------------------------------------------------------------------------------" << std::endl;
				std::cout << "Please choose the new algorithm [1, 2, 3, 4]: " << std::endl;
				std::cin >> algorithm;
				continue;

			case 'C':
			case 'c':
				std::cout << "Please input the new number of CPUs [1, MAXINT]: " << std::endl;
				std::cin >> numCPUs;
				continue;

			case 'I':
			case 'i':			
				std::cout << "Please input the new number of IO devices [1, MAXINT]: " << std::endl;
				std::cin >> numIOs;
				continue;

			case 'M':
			case 'm':
				std::cout << "Please input the new number of memory pages [1, MAXINT]: " << std::endl;
				std::cin >> numPages;
				continue;

			case 'S':
			case 's':		
				std::cout << "Please input the new cost of a context switch [0.0 - 9999.0]: " << std::endl;
				std::cin >> contextSwitchCost;
				continue;

			case 'P':
			case 'p':
				std::cout << "Please input the new cost of a page fault [0.0 - 9999.0]: " << std::endl;			
				std::cin >> pageFaultCost;

			case 'K':
			case 'k':
				std::cout << "Please input the new quantum size for the round-robin ready queue [0.0 - 9999.0]:" << std::endl;
				std::cin >> quantumSize;
				continue;


			case 'B':
			case 'b':
				std::cout << "Please input the new rate of IO bound tasks. (CPU bound " << std::endl;
				std::cout << "tasks will be the complement of this value) [0.0 - 1.0]: " << std::endl;
				std::cin >> taskMixRate;
				continue;

			case 'F':
			case 'f':
				std::cout << "Please input the new frequency of task creation. [1.0 - 9999.0]: " << std::endl;
				std::cin >> taskCreationFrequency;
				continue;

			case 'Q':
			case 'q':
				std::cout << "All right, have a good day!" << std::endl;
				return 0;

			default:
				std::cout << "Sorry, I didn't understand that. Try again." << std::endl;
				continue;
		}

		EventQueue myEventQueue(
			taskCreationFrequency, 
			taskMixRate,
			contextSwitchCost,
			pageFaultCost,
			numCPUs,
			numIOs,
			numPages,
			algorithm,
			quantumSize);

		// myEventQueue.printStartTimes();
		// myEventQueue.printFinishTimes();
		myEventQueue.printThroughput();
		myEventQueue.printLatency();
		myEventQueue.printResponseTimes();
		myEventQueue.printUtilization();


	}



	return 0;
}
