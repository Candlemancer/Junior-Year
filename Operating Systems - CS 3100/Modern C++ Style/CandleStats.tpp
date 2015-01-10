// Jonathan Petersen
// A01236750
// Modern C++ Assignment
// Template Class Definition

#ifdef _CANDLE_STATISTICS

#include <typeinfo>
#include <numeric>
#include <ctime>
#include <array>

// Calculate the Standard Deviation of all the values stored in a container.
// container needs to implement .begin(), .end(), and .size(). All of the
// STL containers should meet this requirement.
template < typename container >
double CandleStats::standardDeviation(container& source) {

	double stdDev = 0;
	double xbar = mean(source);

	// Calculate the sum of squared differences from the mean.
	for (auto&& i : source) {
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
double CandleStats::mean(container& source) {

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
double CandleStats::runningTime(callable const & fn) {

	clock_t clockTicks;

	// Start Timer
	clockTicks = clock();

	// Call Function
	fn();

	// Finish Timer
	clockTicks = clock() - clockTicks;

	return static_cast<double>(clockTicks) / CLOCKS_PER_SEC;
}

// Aggregate funciton of the mean, standard deviation, and timing functions.
// Calculates the mean and standard deviation of the running time of a function.
// callable must implement operator().
template < typename callable >
std::tuple<std::string, double, double> CandleStats::testFunction(std::string name,
		callable const & fn) {

	std::array<double, NUM_TESTS> times;
	std::tuple<std::string, double, double> results;

	// Run the tests NUM_TESTS times.
	std::generate(times.begin(), times.end(),
		[&](){ return runningTime(fn); }
	);

	// Add the statistics to the results
	results = std::make_tuple( name, mean(times), standardDeviation(times) );

	return results;
}

#endif
