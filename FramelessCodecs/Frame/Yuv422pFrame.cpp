#include "Yuv422pFrame.h"

#include <cstdint>

#include <algorithm>
using std::copy;


Yuv422pFrame::Yuv422pFrame(int width, int height) :
	DataFrame(width, height, 2*width*height),
	strides_{width, width/2, width/2},
	offsets_{0, width*height, (width*height)/2*3} {
}

void Yuv422pFrame::resize(int width, int height) {
	DataFrame::resize(width, height, 2*width*height);
	strides_[Y_PLANE]  = width;
	strides_[U_PLANE] = width/2;
	strides_[V_PLANE] = width/2;
	offsets_[Y_PLANE]  = 0;
	offsets_[U_PLANE] = width*height;
	offsets_[V_PLANE] = (width*height)/2*3;
}

uint8_t& Yuv422pFrame::intensityAt(int i) {
	return data()[i];
}

uint8_t& Yuv422pFrame::intensityAt(int plane, int i) {
	return intensityAt(offsets_[plane] + i);
}

uint8_t& Yuv422pFrame::intensityAt(int plane, int x, int y) {
	return intensityAt(plane, y * strides_[plane] + x);
}

Yuv422pFrame& Yuv422pFrame::operator=(Frame& src) {
	resize(src.width(), src.height());
	for (int y = 0; y < height(); y++) {
		for (int x = 0; x < width(); x++) {
			intensityAt(Y_PLANE, x, y) = src.getIntensityAsByte(Y_PLANE, x, y);
		}
	}
	for (int y = 0; y < height(); y++) {
		for (int x = 0; x < width()/2; x++) {
			intensityAt(U_PLANE, x, y) = src.getIntensityAsByte(U_PLANE, x*2, y);
			intensityAt(V_PLANE, x, y) = src.getIntensityAsByte(V_PLANE, x*2, y);
		}
	}
	return *this;
}

uint8_t Yuv422pFrame::getIntensityAsByte(int plane, int x, int y) {
	return intensityAt(plane, (plane == Y_PLANE) ? x : x/2, y);
}

uint16_t Yuv422pFrame::getIntensityAs16Bits(int plane, int x, int y) {
	return static_cast<uint16_t>(intensityAt(plane, (plane == Y_PLANE) ? x : x/2, y)) << 8;
}

double Yuv422pFrame::getIntensityAsDouble(int plane, int x, int y) {
	return static_cast<double>(intensityAt(plane, (plane == Y_PLANE) ? x : x/2, y)) / 0xFF;
}
