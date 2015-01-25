// Jonathan Petersen
// A01236750
// Serial Mandelbrot Assignment
// Portable PixMap Implementation

#include "PortablePixMap.hpp"
#include <algorithm>

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
	std::vector<std::vector<int>> data,
	ImageType fileType,
	int colorDepth
	) :

	FILE_TYPE(fileType),
	WIDTH(data[0].size()),
	HEIGHT(data.size()),
	COLOR_DEPTH(colorDepth),
	pixels(data),
	fout("test.ppm") {

	fout << "P" << FILE_TYPE << std::endl;
	fout << WIDTH << " " << HEIGHT << std::endl;
	if (FILE_TYPE != BITMAP_TXT && FILE_TYPE != BITMAP_BIN) {
		fout << COLOR_DEPTH << std::endl;
	}

	// Convert from bottom up array to top down.
	// std::reverse(pixels.begin(), pixels.end());

	for (auto&& i : pixels) {

		for (auto&& j : i) {

			fout << j << " ";

			if (FILE_TYPE == PIXMAP_TXT || FILE_TYPE == PIXMAP_BIN) {
				fout << j << " " << j << " ";
			}

		}

		fout << std::endl;
	}

	fout.close();
	return;

}
