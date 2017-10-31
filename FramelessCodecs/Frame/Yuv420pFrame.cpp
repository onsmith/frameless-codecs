#include "Yuv420pFrame.h"

#include <cstdint>


Yuv420pFrame::Yuv420pFrame(int width, int height) :
	DataFrame(width, height, (width*height)/2*3),
	strides_{width, width/2, width/2},
	offsets_{0, width*height, (width*height)/4*5} {
}

void Yuv420pFrame::resize(int width, int height) {
	DataFrame::resize(width, height, (width*height)/2*3);
	strides_[Y_PLANE] = width;
	strides_[U_PLANE] = width/2;
	strides_[V_PLANE] = width/2;
	offsets_[Y_PLANE] = 0;
	offsets_[U_PLANE] = width*height;
	offsets_[V_PLANE] = (width*height)/4*5;
}

uint8_t& Yuv420pFrame::intensityAt(int i) {
	return data()[i];
}

uint8_t& Yuv420pFrame::intensityAt(int plane, int i) {
	return intensityAt(offsets_[plane] + i);
}

uint8_t& Yuv420pFrame::intensityAt(int plane, int x, int y) {
	return intensityAt(plane, y * strides_[plane] + x);
}

Yuv420pFrame& Yuv420pFrame::operator=(Frame& src) {
	resize(src.width(), src.height());
	for (int y = 0; y < height(); y++) {
		for (int x = 0; x < width(); x++) {
			intensityAt(Y_PLANE, x, y) = src.getIntensityAsByte(Y_PLANE, x, y);
		}
	}
	for (int y = 0; y < height()/2; y++) {
		for (int x = 0; x < width()/2; x++) {
			intensityAt(U_PLANE, x, y) = src.getIntensityAsByte(U_PLANE, x*2, y*2);
			intensityAt(V_PLANE, x, y) = src.getIntensityAsByte(V_PLANE, x*2, y*2);
		}
	}
	return *this;
}

uint8_t Yuv420pFrame::getIntensityAsByte(int plane, int x, int y) {
	return (plane == Y_PLANE) ? intensityAt(plane, x, y) : intensityAt(plane, x/2, y/2);
}

uint16_t Yuv420pFrame::getIntensityAs16Bits(int plane, int x, int y) {
	return static_cast<uint16_t>((plane == Y_PLANE) ? intensityAt(plane, x, y) : intensityAt(plane, x/2, y/2)) << 8;
}

double Yuv420pFrame::getIntensityAsDouble(int plane, int x, int y) {
	return static_cast<double>((plane == Y_PLANE) ? intensityAt(plane, x, y) : intensityAt(plane, x/2, y/2)) / 0xFF;
}
