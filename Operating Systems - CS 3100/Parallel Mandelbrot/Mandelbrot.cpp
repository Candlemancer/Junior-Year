// Jonathan Petersen
// A01236750
// Serial Mandelbrot Assignment
// Mandelbrot Class Implementation

#include "Mandelbrot.hpp"
#include <algorithm>
#include <thread>
#include <vector>

// #include <iostream>

Mandelbrot::Mandelbrot() :
	viewWidth(640),
	viewHeight(480),
	xLowerBound(-2.0),
	xUpperBound(0.3333333333),
	yLowerBound(-1.0),
	yUpperBound(1.0) {
		generate();
	}

Mandelbrot::Mandelbrot(
	double xLow,
	double xHigh,
	double yLow,
	double yHigh,
	int width,
	int height) :

	viewWidth(width),
	viewHeight(height),
	xLowerBound(xLow),
	xUpperBound(xHigh),
	yLowerBound(yLow),
	yUpperBound(yHigh) {
		generate();
	}


void Mandelbrot::generate(int numThreads) {

	int linesPerThread = viewHeight / numThreads;
	std::vector<std::thread> threads;

	// Clear the Vector
	data.erase(data.begin(), data.end());
	std::fill_n(std::back_inserter(data), viewHeight, std::vector<int>() = {1});

	// Split up the work for each thread
	for (int i = numThreads; i > 0; --i) {

		threads.push_back(
			std::thread(
				[=](){
					generateLines( (linesPerThread * i), linesPerThread * (i - 1) );
				}
			)
		);

	}

	for (auto&& i : threads) {
		i.join();
	}

	return;
}

void Mandelbrot::changeView(double xLow, double yLow, double xHigh, double yHigh) {

	xLowerBound = xLow;
	xUpperBound = xHigh;
	yLowerBound = yLow;
	yUpperBound = yHigh;

	return;
}

void Mandelbrot::changeView(double xMid, double yMid, double yHeight) {

	xLowerBound = xMid - (yHeight / 2.0);
	xUpperBound = xMid + (yHeight / 2.0);
	yLowerBound = yMid - (yHeight / 2.0);
	yUpperBound = yMid + (yHeight / 2.0);

	return;
}

void Mandelbrot::changeSize(int width, int height) {

	viewWidth = width;
	viewHeight = height;

	return;
}


int Mandelbrot::testPoint(double x0, double y0) {

	double iteration    =    0;
	double iterationMax = 8192;
	double x = 0;
	double y = 0;
	double xTemp = 0;
	double yTemp = 0;

	//Count number of iterations
	while(x*x + y*y <= 4 && iteration < iterationMax){

		xTemp = x*x - y*y + x0;
		yTemp = 2 * x * y + y0;
		if (x == xTemp && y == yTemp) {
			iteration = iterationMax;
			break;
		}
		x = xTemp;
		y = yTemp;
		iteration++;
	}

	//Set result to number of iterations, or 0 if no result
	if(iteration == iterationMax) { return 0; }
	return iteration;
}

void Mandelbrot::generateLines(int topLine, int bottomLine) {

	double x = xLowerBound;
	double y = yLowerBound;
	int currentIterations = 0;

	// std::cout << "Start: " << topLine << " End: " << bottomLine << std::endl;

	// Create a Line group for each Thread
	std::vector<int> currentLine;

	// Starting from the top, generate lines left to right.
	for (int i = bottomLine; i < topLine; ++i) {

		// std::cout << i << std::endl;

		y = (i * (yUpperBound - yLowerBound)/viewHeight) + yLowerBound;

		for (int j = 0; j < viewWidth; j++) {

			x = (j * (xUpperBound - xLowerBound)/viewHeight) + xLowerBound;

			// Actually Create the data.
			currentIterations = testPoint(x, y);
			maxValue = std::max(maxValue, currentIterations);
			currentLine.push_back(currentIterations);

		}

		save(currentLine, i);
		currentLine.erase(currentLine.begin(), currentLine.end());

	}

	return;
}

void Mandelbrot::save(std::vector<int> line, int index) {

	std::lock_guard<std::mutex> lock (dataLock);
	data.at(index) = (line);

	return;
}
