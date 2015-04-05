// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// Task Class Header

#ifndef TASK_HPP
#define TASK_HPP

#include <vector>
#include <tuple>
// #include <string>

class Task{
public:
	// Constructors
	// Task();
	Task(double mixRate, int numIOs);

	// Member Functions
	void generate(
		double mixRate,
		int numIOs,
		double meanCPU = 50.0, 
		double stdDevCPU = 0.0, 
		double meanIO = 50.0, 
		double stdDevIO = 0.0);

	void printTask();
	std::tuple<int, double> pop();
	unsigned int size() { return taskList.size(); }
	std::vector<std::tuple<int, double>> getTasks() {return taskList;}

private:
	// Member Variables
	bool isIoBound;
	std::vector<std::tuple<int, double>> taskList;
	int const CPU = -1;

};

#endif
