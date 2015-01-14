// Jonathan Petersen
// A01236750
// Modern C++ Assignment
// Driver Code

#include <iostream>
#include "CandleStats.hpp"

void myFunction(int x);

int main() {

	CandleStats myTest("Hello World",
		[](){ fprintf(stderr, "Hello World! \r"); }
	);
	myTest.printResults();

	CandleStats yourTest("My Function",
		[](){ myFunction(7); }
	);
	yourTest.printResults();

	return 0;
}

void myFunction(int x) {
	int a = 5;
	int b = 7;
	int c = 5 * 7;
	int d = x;

	return;
}
