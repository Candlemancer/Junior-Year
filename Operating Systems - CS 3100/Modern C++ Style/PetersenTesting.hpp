// Jonathan Petersen
// A01236750
// Modern C++ Assignment
// Template Class Definition

#ifndef PETERSEN_TESTING_H
#define PETERSEN_TESTING_H

#include <vector>

class PetersenTesting {

public:
	// PetersenTesting();

	double standardDeviation(std::vector<float> source);
	double mean(std::vector<float> source);
	double runningTime();
	std::vector<double> testFunction();

private:
	int static const NUM_TEST_FUNCTIONS;
	// double m_standardDeviation;
	// double m_mean;
	// double m_runningTime;

};

#endif
