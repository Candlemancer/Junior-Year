// Jonathan Petersen
// A01236750
// Modern C++ Assignment
// Driver Code

#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include "CandleStats.hpp"

void myFunction(int x);

int main() {

	CandleStats myTest;
	std::vector< std::tuple<std::string, double, double> > result;

	// Setup the Tests
	result.push_back(
		myTest.testFunction("Hello World",
			[](){ fprintf(stderr, "Hello World \r"); }
		)

	);

	result.push_back(
		myTest.testFunction("MyFunction",
			[](){ myFunction(7); }
		)
	);

	// Show the results
	for (auto&& line : result) {
		// printf("%s \n", std::get<0>(line).c_str(), std::ge );
		printf("| %-20s Mean: %0.16f sec., Standard Deviation: %0.16f sec.\n",
				std::get<0>(line).c_str(), std::get<1>(line), std::get<2>(line) );
	}

	return 0;
}

void myFunction(int x) {
	int a = 5;
	int b = 7;
	int c = 5 * 7;
	int d = x;

	return;
}
