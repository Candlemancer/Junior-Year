// Jonathan Petersen
// A01236750
// Serial Mandelbrot Assignment
// Mandelbrot Class Implementation

#include "Mandelbrot.hpp"
#include <algorithm>

Mandelbrot::Mandelbrot() :
	viewWidth(640),
	viewHeight(480),
	xLowerBound(-2.0),
	xUpperBound(0.3333333333),
	yLowerBound(-1.0),
	yUpperBound(1.0) {
		generate();
	}

void Mandelbrot::generate() {

	double x = xLowerBound;
	double y = yLowerBound;
	int currentIterations = 0;
	std::vector<int> currentLine;

	for (int i = viewHeight; i > 0; i--) {

		y = (i * (yUpperBound - yLowerBound)/viewHeight) + yLowerBound;

		for (int j = 0; j < viewWidth; j++) {

			x = (j * (xUpperBound - xLowerBound)/viewHeight) + xLowerBound;

			currentIterations = testPoint(x, y);
			maxValue = std::max(maxValue, currentIterations);
			currentLine.push_back(currentIterations);

		}

		data.push_back(currentLine);
		currentLine.erase(currentLine.begin(), currentLine.end());

	}
}

void Mandelbrot::changeView(double xLow, double yLow, double xHigh, double yHigh) {

	data.erase(data.begin(), data.end());

	xLowerBound = xLow;
	xUpperBound = xHigh;
	yLowerBound = yLow;
	yUpperBound = yHigh;

	generate();
	return;
}

void Mandelbrot::changeView(double xMid, double yMid, double yHeight) {

	data.erase(data.begin(), data.end());

	xLowerBound = xMid - ((yHeight + (1.0 / 3.0)) / 2.0);
	xUpperBound = xMid + ((yHeight + (1.0 / 3.0)) / 2.0);
	yLowerBound = yMid - (yHeight / 2.0);
	yUpperBound = yMid + (yHeight / 2.0);

	generate();
	return;
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
