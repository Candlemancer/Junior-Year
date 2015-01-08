#include "PetersenTesting.hpp"

#include <iostream>

int const PetersenTesting::NUM_TEST_FUNCTIONS = 2;

double PetersenTesting::standardDeviation(std::vector<float> source) {

	return 3.4;
}

double PetersenTesting::mean(std::vector<float> source) {

	return 4.5;
}

double PetersenTesting::runningTime() {

	return 5.2;
}

std::vector<double> PetersenTesting::testFunction() {

	std::vector<double> result;
	result.push_back(2.1);
	result.push_back(2.2);
	result.push_back(2.3);

	// std::vector<float> test1;
	// test1.push_back(4.5);
	// test1.push_back(5.3);
	// test1.push_back(9.2);

	// std::vector<float> test2;
	// test1.push_back(4.5);
	// test1.push_back(5.3);
	// test1.push_back(9.2);

	return result;
}

