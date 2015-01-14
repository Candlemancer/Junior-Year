// Jonathan Petersen
// A01236750
// Modern C++ Assignment
// Template Class Definition

#ifndef _CANDLE_STATISTICS
#define _CANDLE_STATISTICS

#include <vector>
#include <string>
#include <chrono>

class CandleStats {

public:
	template <typename Callable>
		CandleStats(std::string name, Callable const & fn, int numTests = 1000000);

	double const getMean() { return mean; }
	double const getStandardDeviation() { return stdDev; }
	std::string const getName() { return functionName; }
	void const printResults();

private:
	void calculateMean();
	void calculateStandardDeviation();
	template <typename Callable> std::chrono::duration<double>
		calculateRunningTime(Callable const & fn);

	// Number of running times to gather for the tests
	int const NUM_TESTS;

	double mean;
	double stdDev;
	std::string functionName;
	std::vector<std::chrono::duration<double>> times;

};

#include "CandleStats.tpp"
#endif
