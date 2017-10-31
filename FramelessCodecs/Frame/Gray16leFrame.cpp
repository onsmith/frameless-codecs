#include "Gray16leFrame.h"

#include <cstdint>


Gray16leFrame::Gray16leFrame(int width, int height) :
	DataFrame(width, height, width*height) {
}

void Gray16leFrame::resize(int width, int height) {
	DataFrame::resize(width, height, width*height);
}

uint16_t& Gray16leFrame::intensityAt(int i) {
	return data()[i];
}

uint16_t& Gray16leFrame::intensityAt(int x, int y) {
	return intensityAt(y*width() + x);
}

Gray16leFrame& Gray16leFrame::operator=(Frame& src) {
	resize(src.width(), src.height());
	for (int y = 0; y < height(); y++) {
		for (int x = 0; x < width(); x++) {
			intensityAt(x, y) = src.getIntensityAs16Bits(Y_PLANE, x, y);
		}
	}
	return *this;
}

uint8_t Gray16leFrame::getIntensityAsByte(int plane, int x, int y) {
	return (plane == Y_PLANE) ? static_cast<uint8_t>(intensityAt(x, y) >> 8) : 0x80;
}

uint16_t Gray16leFrame::getIntensityAs16Bits(int plane, int x, int y) {
	return (plane == Y_PLANE) ? intensityAt(x, y) : 0x8000;
}

double Gray16leFrame::getIntensityAsDouble(int plane, int x, int y) {
	return (plane == Y_PLANE) ? static_cast<double>(intensityAt(x, y)) / 0xFFFF : 0.5;
}
