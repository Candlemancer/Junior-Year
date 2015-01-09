#include <iostream>
#include <vector>
#include "CandleStats.hpp"

void myFunction();

int main() {

	CandleStats myTest;
	void (*functionPtr)(void) = &myFunction;
	std::vector< std::vector<double> > result;

	// Setup the Tests
	result.push_back(
		myTest.testFunction([](){
			std::cout << "Hello World \r";
		})
	);

	result.push_back(
		myTest.testFunction(myFunction)
	);

	// Show the results
	for (int i = 0; i < result.size(); ++i)
	{
		printf("Mean: %0.20f sec., Standard Deviation: %0.20f sec.\n", result[0][i], result[0][i]);
	}

	return 0;
}

void myFunction() {
	int a = 5;
	int b = 7;
	int c = 5 * 7;

	return;
}
