// Jonathan Petersen
// A01236750
// Modern C++ Assignment
// Template Class Definition

#include <iostream>
#include <numeric>
#include <ctime>

// Calculate the Standard Deviation of all the values stored in a container.
// container needs to implement .begin(), .end(), and .size(). All of the
// STL containers should meet this requirement.
template < typename container >
double PetersenTesting::standardDeviation(container& source) {

	double stdDev = 0;
	double xbar = mean(source);

	// Calculate the sum of squared differences from the mean.
	for (auto i : source) {
		stdDev += (i - xbar) * (i - xbar);
	}

	// Divide by n - 1.
	stdDev = stdDev / (static_cast<double>(source.size()) - 1.0);

	return stdDev;
}

// Calculate the arithmetic mean of all the values stored in a container.
// container needs to implement .begin(), .end(), and .size(). All of the
// STL containers should meet this requirement.
template < typename container >
double PetersenTesting::mean(container& source) {

	// Compute the sum of the values
	// Accumulate needs a double as the third paramater, otherwise it casts to int.
	double xbar = std::accumulate(source.begin(), source.end(), 0.0);

	// Divide by the number of values
	xbar = xbar / static_cast<double>(source.size());

	return xbar;
}

// Calculate the amount of time a given function takes to run.
// callable must implement operator().
template < typename callable >
double PetersenTesting::runningTime(callable fn) {

	clock_t clockTicks;
	clockTicks = clock();
	fn();
	clockTicks = clock() - clockTicks;

	// printf("%lu \n", clockTicks / CLOCKS_PER_SEC);

	return static_cast<double>(clockTicks) / CLOCKS_PER_SEC;
}

// Aggregate funciton of the mean, standard deviation, and timing functions.
// Calculates the mean and standard deviation of the running time of a function.
// callable must implement operator().
template < typename callable >
std::vector<double> PetersenTesting::testFunction(callable fn) {

	std::vector<double> times;
	std::vector<double> result;

	for (int i = 0; i < NUM_TESTS; ++i) {
		times.push_back(runningTime(fn));
	}

	// for (double i : times) {
	// 	printf("%0.20f \n", i);
	// }

	// std::cout << CLOCKS_PER_SEC << std::endl;

	result.push_back(mean(times));
	result.push_back(standardDeviation(times));

	return result;
}

