#include "Yuv444pFrame.h"

#include <cstdint>


Yuv444pFrame::Yuv444pFrame(int width, int height) :
	DataFrame(width, height, width*height*3),
	numPixels_(width*height) {
}

void Yuv444pFrame::resize(int width, int height) {
	numPixels_ = width*height;
	DataFrame::resize(width, height, 3*numPixels_);
}

uint8_t& Yuv444pFrame::intensityAt(int i) {
	return data()[i];
}

uint8_t& Yuv444pFrame::intensityAt(int plane, int i) {
	return intensityAt(plane*numPixels_ + i);
}

uint8_t& Yuv444pFrame::intensityAt(int plane, int x, int y) {
	return intensityAt(plane, y*width() + x);
}

Yuv444pFrame& Yuv444pFrame::operator=(Frame& src) {
	resize(src.width(), src.height());
	for (int y = 0; y < height(); y++) {
		for (int x = 0; x < width(); x++) {
			intensityAt(Y_PLANE, x, y) = src.getIntensityAsByte(Y_PLANE, x, y);
			intensityAt(U_PLANE, x, y) = src.getIntensityAsByte(U_PLANE, x, y);
			intensityAt(V_PLANE, x, y) = src.getIntensityAsByte(V_PLANE, x, y);
		}
	}
	return *this;
}

uint8_t Yuv444pFrame::getIntensityAsByte(int plane, int x, int y) {
	return intensityAt(plane, x, y);
}

uint16_t Yuv444pFrame::getIntensityAs16Bits(int plane, int x, int y) {
	return static_cast<uint16_t>(intensityAt(plane, x, y)) << 8;
}

double Yuv444pFrame::getIntensityAsDouble(int plane, int x, int y) {
	return static_cast<double>(intensityAt(plane, x, y)) / 0xFF;
}
