// Jonathan Petersen
// A01236750
// Serial Mandelbrot Assignment
// Mandelbrot Header class

#ifndef _MANDELBROT_HPP
#define _MANDELBROT_HPP

#include <vector>
#include <mutex>


class Mandelbrot {

public:

	Mandelbrot();
	Mandelbrot(
		double xLow,
		double xHigh,
		double yLow,
		double yHigh,
		int width = 640,
		int height = 480
	);

	void generate(int numThreads = 1);
	void changeView(double xLow, double yLow, double xHigh, double yHigh);
	void changeView(double xMid, double yMid, double yScale);
	void changeSize(int width, int height);

	int getMax() { return maxValue; }
	std::vector<std::vector<int>> getData() { return data; }


private:

	int testPoint(double x0, double y0);
	void generateLines(int topLine, int bottomLine = 0);
	void save(std::vector<int> line, int index);

	int viewWidth;
	int viewHeight;
	int maxValue;
	double xLowerBound;
	double xUpperBound;
	double yLowerBound;
	double yUpperBound;

	std::mutex dataLock;
	std::vector<std::vector<int>> data;

};

#endif
