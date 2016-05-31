// Jonathan Petersen
// A01236750
// Modern C++ Assignment
// Template Class Definition

#ifdef _CANDLE_STATISTICS

#include <algorithm>
#include <typeinfo>
#include <numeric>
#include <ctime>
#include <array>
#include <cmath>


template < typename Callable >
CandleStats::CandleStats(std::string name, Callable const & fn, int numTests) :
	NUM_TESTS(numTests),
	functionName(name) {

	// Run the tests NUM_TESTS times.
	std::generate_n(std::back_inserter(times), numTests,
		[&](){ return calculateRunningTime(fn); }
	);

	// Add the statistics to the results
	calculateMean();
	calculateStandardDeviation();

	return;

}

void CandleStats::printResults() {

	printf("| %32s - Mean: %0.16f sec. Standard Deviation: %0.16f sec.\n",
		functionName.c_str(),
		mean,
		stdDev);

	return;
}


void CandleStats::calculateMean() {

	mean = std::accumulate(times.cbegin(), times.cend(), times[0].zero()).count();
	mean = mean / times.size();

	return;
}

void CandleStats::calculateStandardDeviation() {

	std::vector<double> differences (times.size());
	for (auto&& i : times) {
		differences.push_back( (i.count() - mean) * (i.count() - mean) );
	}
	stdDev = std::accumulate(differences.cbegin(), differences.cend(), 0.0);
	stdDev = stdDev / (differences.size() - 1);
	stdDev = std::sqrt(stdDev);

	return;
}

// Calculate the amount of time a given function takes to run.
// callable must implement operator().
template < typename Callable >
std::chrono::duration<double> CandleStats::calculateRunningTime(Callable const & fn) {

	using std::chrono::system_clock;

	system_clock::time_point start = system_clock::now();
	fn();
	system_clock::time_point stop = system_clock::now();

	return stop - start;
}


#endif
