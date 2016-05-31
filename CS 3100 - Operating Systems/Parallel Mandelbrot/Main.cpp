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
#include "CandleStats.hpp"

int main() {
    Mandelbrot myMandelbrot(2, 2, 2, 2, 6, 4);
    std::stringstream ss;

    // Setup View Window
    // myMandelbrot.changeView(-0.6, 0.5, -0.4, 0.7);
    myMandelbrot.changeView(-0.44005, 0.56, 0.00005);

    myMandelbrot.changeSize(512, 512);
    // myMandelbrot.generate(4);

    // Begin Tests
    for (int i = 8; i <= 8; i++) {
        // myMandelbrot.changeSize((2880 / 100.0) * i, (1800 / 100.0) * i);
        std::cout << "..."
                  << "\r";

        ss << "(" << i << " cores) "
           << "Mandelbrot";
        CandleStats myTest(ss.str(),  // Label to print
                           [&]() { myMandelbrot.generate(i); },
                           2  // Number of times to repeat the test
                           );
        myTest.printResults();
        ss.str("");
    }

    PortablePixMap myPixMap(myMandelbrot.getData(), PortablePixMap::GRAYMAP_TXT,
                            myMandelbrot.getMax());

    return 0;
}
