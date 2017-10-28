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

Yuv444pFrame& Yuv444pFrame::operator=(Yuv422pFrame& const src) {
	resize(src.width(), src.height());
	copy(src.data(), src.data() + numPixels_, data());
	for (int i = 0; i < numPixels_; i++) {
		intensityAt(U_PLANE, i) = src.intensityAt(Yuv422pFrame::U_PLANE, i/2);
		intensityAt(V_PLANE, i) = src.intensityAt(Yuv422pFrame::V_PLANE, i/2);
	}
	return *this;
}

Yuv444pFrame& Yuv444pFrame::operator=(Yuv420pFrame& const src) {
	resize(src.width(), src.height());
	copy(src.data(), src.data() + width()*height(), data());
	for (int y = 0; y < height(); y++) {
		for (int x = 0; x < width(); x++) {
			intensityAt(U_PLANE, x, y) = src.intensityAt(Yuv420pFrame::U_PLANE, x/2, y/2);
			intensityAt(V_PLANE, x, y) = src.intensityAt(Yuv420pFrame::V_PLANE, x/2, y/2);
		}
	}
	return *this;
}

Yuv444pFrame& Yuv444pFrame::operator=(GrayDoubleFrame& const src) {
	resize(src.width(), src.height());
	for (int i = 0; i < width()*height(); i++) {
		intensityAt(Y_PLANE, i) = static_cast<uint8_t>(src.intensityAt(i) * 0xFF);
		intensityAt(U_PLANE, i) = 0x80;
		intensityAt(V_PLANE, i) = 0x80;
	}
	return *this;
}

Yuv444pFrame& Yuv444pFrame::operator=(Gray16leFrame& const src) {
	resize(src.width(), src.height());
	for (int i = 0; i < width()*height(); i++) {
		intensityAt(Y_PLANE, i) = static_cast<uint8_t>(src.intensityAt(i) >> 8);
		intensityAt(U_PLANE, i) = 0x80;
		intensityAt(V_PLANE, i) = 0x80;
	}
	return *this;
}
