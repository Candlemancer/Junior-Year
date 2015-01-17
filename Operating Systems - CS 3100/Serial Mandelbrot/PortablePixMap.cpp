// Jonathan Petersen
// A01236750
// Serial Mandelbrot Assignment
// Portable PixMap Implementation

#include "PortablePixMap.hpp"

PortablePixMap::PortablePixMap() :
	FILE_TYPE(BITMAP_TXT),
	WIDTH(16),
	HEIGHT(16),
	COLOR_DEPTH(16),
	pixels(),
	fout() {
		// Empty
	}

PortablePixMap::PortablePixMap(
	std::vector<std::vector<int>>& data,
	ImageType fileType,
	int width,
	int height,
	int colorDepth
	) :

	FILE_TYPE(fileType),
	WIDTH(width),
	HEIGHT(height),
	COLOR_DEPTH(colorDepth),
	pixels(data),
	fout("test.txt") {

		fout << FILE_TYPE << std::endl;
		fout << WIDTH << " " << HEIGHT << std::endl;
		if (FILE_TYPE != BITMAP_TXT || FILE_TYPE != BITMAP_BIN) {
			fout << COLOR_DEPTH << std::endl;
		}

	}
