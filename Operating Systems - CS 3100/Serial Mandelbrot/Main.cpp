// Jonathan Petersen
// A01236750
// Serial Mandelbrot Assignment
// Driver Code

// Adapted from my previous mandelbrot assignment.
#include <vector>

#include "PortablePixMap.hpp"
#include "Mandelbrot.hpp"


int main() {

	Mandelbrot myMandelbrot;

	// std::vector<std::vector<int>> myData;
	// std::vector<int> v1 {1, 0, 1, 0, 1};
	// std::vector<int> v2 {0, 1, 0, 1, 0};
	// std::vector<int> v3 {3, 0, 3, 0, 3};
	// std::vector<int> v4 {0, 1, 0, 1, 0};
	// std::vector<int> v5 {1, 0, 1, 0, 1};

	// myData.push_back(v1);
	// myData.push_back(v2);
	// myData.push_back(v3);
	// myData.push_back(v4);
	// myData.push_back(v5);
	// myData = myMandelbrot.getData();

	// myMandelbrot.changeView(-0.6, 0.5, -0.4, 0.7);
	myMandelbrot.changeView(-0.5, 0.7, 0.5);

	PortablePixMap myPixMap(
		myMandelbrot.getData(),
		PortablePixMap::GRAYMAP_TXT,
		myMandelbrot.getMax()
	);

	return 0;
}
