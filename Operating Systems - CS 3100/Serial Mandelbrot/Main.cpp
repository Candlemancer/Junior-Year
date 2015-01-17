// Jonathan Petersen
// A01236750
// Serial Mandelbrot Assignment
// Driver Code

// Adapted from my previous mandelbrot assignment.
#include <vector>

#include "PortablePixMap.hpp"


int main() {

	std::vector<std::vector<int>> myData;
	std::vector<int> v1 {1, 0, 1, 0, 1};
	std::vector<int> v2 {0, 1, 0, 1, 0};
	std::vector<int> v3 {1, 0, 1, 0, 1};
	std::vector<int> v4 {0, 1, 0, 1, 0};
	std::vector<int> v5 {1, 0, 1, 0, 1};

	myData.push_back(v1);
	myData.push_back(v2);
	myData.push_back(v3);
	myData.push_back(v4);
	myData.push_back(v5);

	PortablePixMap myPixMap(myData);

	return 0;
}
