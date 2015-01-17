// Jonathan Petersen
// A01236750
// Serial Mandelbrot Assignment
// Mandelbrot Class Implementation

#include "Mandelbrot.hpp"

Mandelbrot::Mandelbrot() :
	viewWidth(640),
	viewHeight(480),
	xLowerBound(-3.0),
	xUpperBound(3.0),
	yLowerBound(-3.0),
	yUpperBound(3.0) {
		generate();
	}

void Mandelbrot::generate() {

	double x = xLowerBound;
	double y = yLowerBound;
	std::vector<int> currentLine;

	for (int i = 0; i < viewHeight; i++) {

		y = (i * (yUpperBound - yLowerBound)/viewHeight) + yLowerBound;

		for (int j = 0; j < viewWidth; j++) {

			x = (j * (xUpperBound - xLowerBound)/viewHeight) + xLowerBound;

			currentLine.push_back( testPoint(x, y) );
		}

		data.push_back(currentLine);
		currentLine.erase(currentLine.begin(), currentLine.end());

	}
}

int Mandelbrot::testPoint(double x0, double y0) {

	double iteration    =    0;
	double iterationMax = 4096;
	double t = 0;
	double x = 0;
	double y = 0;
	double z = 0;

	//Count number of iterations
	while(x*x + y*y <= 2 && iteration < iterationMax){

		t = 2 * x * y + y0;
		x = x*x - y*y + x0;
		y = t;

		iteration++;
	}

	//Set result to number of iterations, or 0 if no result
	if(iteration != iterationMax) z = iteration;
	if(iteration == iterationMax) z = 0;

	return z;
}
