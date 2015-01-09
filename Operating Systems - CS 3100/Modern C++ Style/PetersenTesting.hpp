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

	template <typename container> double standardDeviation(container& source);
	template <typename container> double mean(container& source);
	template <typename callable> double runningTime(callable fn);
	template <typename callable> std::vector<double> testFunction(callable fn);

private:
	int static const NUM_TESTS = 1000000;

	// int static const NUM_TEST_FUNCTIONS;
	// double m_standardDeviation;
	// double m_mean;
	// double m_runningTime;

};

#include "PetersenTesting.tpp"
#endif
