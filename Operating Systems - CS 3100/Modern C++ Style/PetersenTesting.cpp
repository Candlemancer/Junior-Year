#include "PetersenTesting.hpp"

#include <iostream>

double PetersenTesting::standardDeviation() {

	return 3.4;
}

double PetersenTesting::mean() {

	return 4.5;
}

double PetersenTesting::runningTime() {

	return 5.2;
}

void PetersenTesting::testFunction() {

	std::cout << standardDeviation() << " " << mean() << " " << runningTime() << std::endl;
	return;
}
