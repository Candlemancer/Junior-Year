#include <iostream>
#include <vector>
#include "PetersenTesting.hpp"

int main() {

	PetersenTesting myTest;

	std::vector<double> result;
	result = myTest.testFunction([](){
		std::cout << "Hello World" << std::endl;
	});

	printf("Mean: %0.20f, Standard Deviation: %0.20f \n", result[0], result[1]);
	// result.push_back(2.1);
	// result.push_back(2.8);
	// result.push_back(2.1);

	// printf("%0.2f \n", myTest.mean(result));
	// printf("%0.2f \n", myTest.standardDeviation(result));
	// printf("%d \n", myTest.runningTime([](){
	// 	std::cout << "Hello World!" << std::endl;
	// }));



	return 0;
}
