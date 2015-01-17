// Jonathan Petersen
// A01236750
// Serial Mandelbrot Assignment
// Portable PixMap Header

#ifndef _PORTABLE_PIX_MAP_H
#define _PORTABLE_PIX_MAP_H

#include <vector>
#include <fstream>

class PortablePixMap{

public:

	enum ImageType {
		BITMAP_TXT,
		GRAYMAP_TXT,
		PIXMAP_TXT,
		BITMAP_BIN,
		GRAYMAP_BIN,
		PIXMAP_BIN
	};

	PortablePixMap();
	PortablePixMap(
		std::vector<std::vector<int>>& data,
		ImageType fileType = BITMAP_TXT,
		int width = 16,
		int height = 16,
		int colorDepth = 16
		);

private:

	ImageType const FILE_TYPE;
	int const WIDTH;
	int const HEIGHT;
	int const COLOR_DEPTH;
	int static const NUM_FILES = 0;

	std::vector<std::vector<int>> pixels;
	std::ofstream fout;

};

#endif
