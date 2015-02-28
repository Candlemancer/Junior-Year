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
	Task();
	Task(bool ioBound);

	// Member Functions
	void generate(
		double meanCPU = 50.0, 
		double stdDevCPU = 0.0, 
		double meanIO = 50.0, 
		double stdDevIO = 0.0);
	
	void printTask();
	std::vector<std::tuple<int, double>> getTask() {return taskList;}

private:
	// Member Variables
	bool isIoBound;
	std::vector<std::tuple<int, double>> taskList;
	int const CPU = -1;

};

#endif
