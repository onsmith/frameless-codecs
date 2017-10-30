#include "Yuv444pFrame.h"

#include <cstdint>

#include <algorithm>
using std::copy;


Yuv444pFrame::Yuv444pFrame(int width, int height) :
	DataFrame(width, height, width*height*3),
	numPixels_(width*height) {
}

void Yuv444pFrame::resize(int width, int height) {
	numPixels_ = width*height;
	DataFrame::resize(width, height, 3*numPixels_);
}

uint8_t& Yuv444pFrame::intensityAt(int i) const {
	return data()[i];
}

uint8_t& Yuv444pFrame::intensityAt(int plane, int i) const {
	return intensityAt(plane*numPixels_ + i);
}

uint8_t& Yuv444pFrame::intensityAt(int plane, int x, int y) const {
	return intensityAt(plane, y*width() + x);
}

Yuv444pFrame& Yuv444pFrame::operator=(Frame& const src) {
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

uint8_t Yuv444pFrame::getIntensityAsByte(int plane, int i) const {
	return intensityAt(plane, i);
};

uint8_t Yuv444pFrame::getIntensityAsByte(int plane, int x, int y) const {
	return intensityAt(plane, x, y);
};

uint16_t Yuv444pFrame::getIntensityAs16Bits(int plane, int i) const {
	return static_cast<uint16_t>(intensityAt(plane, i)) << 8;
};

uint16_t Yuv444pFrame::getIntensityAs16Bits(int plane, int x, int y) const {
	return static_cast<uint16_t>(intensityAt(plane, x, y)) << 8;
};

double Yuv444pFrame::getIntensityAsDouble(int plane, int i) const {
	return static_cast<double>(intensityAt(plane, i)) / 0xFF;
};

double Yuv444pFrame::getIntensityAsDouble(int plane, int x, int y) const {
	return static_cast<double>(intensityAt(plane, x, y)) / 0xFF;
};
