// Jonathan Petersen
// A01236750
// Modern C++ Assignment
// Template Class Definition

#ifndef _CANDLE_STATISTICS
#define _CANDLE_STATISTICS

#include <vector>
#include <string>

class CandleStats {

public:
	template <typename container> double standardDeviation(container const & source);
	template <typename container> double mean(container const & source);
	template <typename callable> double runningTime(callable const & fn);
	template <typename callable> std::tuple<std::string, double, double>
			testFunction(std::string name, callable const & fn);

private:
	// Number of running times to gather for the tests
	int static const NUM_TESTS = 1000000;
	int static const NUM_RESULTS = 2;

};

#include "CandleStats.tpp"
#endif
