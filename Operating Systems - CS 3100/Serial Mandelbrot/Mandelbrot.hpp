// Jonathan Petersen
// A01236750
// Serial Mandelbrot Assignment
// Mandelbrot Header class

#ifndef _MANDELBROT_HPP
#define _MANDELBROT_HPP

#include <vector>

class Mandelbrot {

public:

	Mandelbrot();
	void generate();
	void changeView(double xLow, double yLow, double xHigh, double yHigh);
	void changeView(double xMid, double yMid, double yScale);
	int getMax() { return maxValue; }
	std::vector<std::vector<int>> getData() { return data; }


private:

	int testPoint(double x0, double y0);

	int viewWidth;
	int viewHeight;
	int maxValue;
	double xLowerBound;
	double xUpperBound;
	double yLowerBound;
	double yUpperBound;

	std::vector<std::vector<int>> data;

};

#endif
