// Jonathan Petersen
// A01236750
// Serial Mandelbrot Assignment
// Driver Code

// Adapted from my previous mandelbrot assignment.
#include <vector>
#include <limits>
#include <sstream>
#include <iostream>

#include "PortablePixMap.hpp"
#include "Mandelbrot.hpp"
#include "../Modern C++ Style/CandleStats.hpp"


int main() {

	Mandelbrot myMandelbrot(2, 2, 2, 2, 6, 4);
	std::stringstream ss;

	// Setup View Window
	// myMandelbrot.changeView(-0.6, 0.5, -0.4, 0.7);
	myMandelbrot.changeView(-0.44005, 0.56, 0.00005);

	myMandelbrot.changeSize(640, 480);
	myMandelbrot.generate(8);

	// Begin Tests
	// for (int i = 1; i <= 50; i++) {
	// 	myMandelbrot.changeSize((2880 / 100.0) * i, (1800 / 100.0) * i);

	// 	ss << "(" << i << ") " << "Mandelbrot "
	// 		<< ((2880 / 100.0) * i) << " x " << ((1800 / 100.0) * i);
	// 	CandleStats myTest(ss.str(),
	// 		[&](){ myMandelbrot.generate(); },
	// 		3
	// 	);
	// 	myTest.printResults();
	// 	ss.str("");

	// }

	PortablePixMap myPixMap(
		myMandelbrot.getData(),
		PortablePixMap::GRAYMAP_TXT,
		myMandelbrot.getMax()
	);

	return 0;
}
