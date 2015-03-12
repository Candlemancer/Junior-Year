// Jonathan Petersen
// A01236750
// Collision Framework Assignment
// Task Class Implementation

#include "Task.hpp"

#include <cmath>
#include <chrono>
#include <random>
#include <iomanip>
#include <iostream>
#include <functional>

// Task::Task() :
// 	isIoBound(false) {

// 	generate(0.5);

// 	return;
// }

Task::Task(double mixRate, int numIOs) {

	generate(mixRate, numIOs);

	return;
}

void Task::generate(
	double mixRate, 
	int numIOs,
	double meanCPU, 
	double stdDevCPU, 
	double meanIO, 
	double stdDevIO) {
	
	// Setup the Random Generator
	std::default_random_engine generator;
	generator.seed(std::chrono::system_clock::now().time_since_epoch().count());

	// Determine IO or CPU bound
	std::uniform_real_distribution<double> taskMix (0.0, 1.0);
	if (taskMix(generator) > mixRate) { isIoBound = true; }
	else { isIoBound = false; }

	// std::cout << "IO bound? " << isIoBound << std::endl;

	// Create Distribution of tasks
	if (isIoBound) {
		meanCPU = 20.0;
		stdDevCPU = 5.0;

		meanIO = 50.0;
		stdDevIO = 15.0;
	}
	else {
		meanCPU = 50.0;
		stdDevCPU = 15.0;

		meanIO = 20.0;
		stdDevIO = 5.0;
	}
	std::normal_distribution<double> distCPU (meanCPU, stdDevCPU);
	std::normal_distribution<double> distIO (meanIO, stdDevIO);
	std::uniform_int_distribution<int> distDevice (0, numIOs - 1);
	auto timeCPU = std::bind(distCPU, generator);
	auto timeIO = std::bind(distIO, generator);
	auto destIO = std::bind(distDevice, generator);

	// Create number of tasks
	std::uniform_int_distribution<int> numTasks (1, 100);

	// Create First CPU Task
	taskList.push_back(std::make_tuple(CPU, fabs(timeCPU())));

	for (int i = 0; i < numTasks(generator); ++i) {
		// Create IO Burst
		taskList.push_back(std::make_tuple(destIO(), fabs(timeIO())));

		// Create CPU Task
		taskList.push_back(std::make_tuple(CPU, fabs(timeCPU())));		
	}



	return;
}

// Prints out the current task list
void Task::printTask() {

	if (taskList.empty()) {
		std::cerr << "TaskList is Empty" << std::endl;
		return;
	}

	for (unsigned int i = 0; i < taskList.size(); ++i) {
		std::cout << std::setw(3) << i << 
			": (" << std::setw(2) << std::get<0>(taskList[i]) << 
			", " << std::setprecision(10) << std::get<1>(taskList[i]) << 
			")" << std::endl;
	}

	return;
}

std::tuple<int, double> Task::pop() {
	auto popped = taskList.front();
	taskList.erase(taskList.begin());

	return popped;
}
