// Jonathan Petersen
// A01236750
// Modern C++ Assignment
// Template Class Definition

#ifndef _CANDLE_STATISTICS
#define _CANDLE_STATISTICS

#include <vector>

class CandleStats {

public:
	template <typename container> double standardDeviation(container& source);
	template <typename container> double mean(container& source);
	template <typename callable> double runningTime(callable const & fn);
	template <typename callable> std::vector<double> testFunction(callable const & fn);

private:
	// Number of running times to gather for the tests
	int static const NUM_TESTS = 1000000;

};

#include "CandleStats.tpp"
#endif
