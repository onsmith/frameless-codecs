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

uint16_t& Gray16leFrame::intensityAt(int _, int x, int y) {
	return intensityAt(x, y);
}

Gray16leFrame& Gray16leFrame::operator=(Frame& src) {
	resize(src.width(), src.height());
	for (int y = 0; y < height(); y++) {
		for (int x = 0; x < width(); x++) {
			intensityAt(LUMA_PLANE, x, y) = src.getIntensityAs16Bits(Y_PLANE, x, y);
		}
	}
	return *this;
}

uint8_t Gray16leFrame::getIntensityAsByte(int plane, int i) {
	return (plane == 0) ? static_cast<uint8_t>(intensityAt(i) >> 8) : 0x80;
}

uint8_t Gray16leFrame::getIntensityAsByte(int plane, int x, int y) {
	return (plane == 0) ? static_cast<uint8_t>(intensityAt(x, y) >> 8) : 0x80;
}

uint16_t Gray16leFrame::getIntensityAs16Bits(int plane, int i) {
	return intensityAt(plane, i);
}

uint16_t Gray16leFrame::getIntensityAs16Bits(int plane, int x, int y) {
	return intensityAt(plane, x, y);
}

double Gray16leFrame::getIntensityAsDouble(int plane, int i) {
	return static_cast<double>(intensityAt(plane, i)) / 0xFFFF;
}

double Gray16leFrame::getIntensityAsDouble(int plane, int x, int y) {
	return static_cast<double>(intensityAt(plane, x, y)) / 0xFFFF;
}
