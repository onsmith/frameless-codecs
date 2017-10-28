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

uint8_t& Yuv422pFrame::intensityAt(int i) const {
	return data()[i];
}

uint8_t& Yuv422pFrame::intensityAt(int plane, int i) const {
	return intensityAt(offsets_[plane] + i);
}

uint8_t& Yuv422pFrame::intensityAt(int plane, int x, int y) const {
	return intensityAt(plane, y * strides_[plane] + x);
}

Yuv422pFrame& Yuv422pFrame::operator=(Yuv444pFrame& const src) {
	resize(src.width(), src.height());
	copy(src.data(), src.data() + width()*height(), data());
	for (int i = 0; i < (width()*height())/2; i++) {
		intensityAt(U_PLANE, i) = src.intensityAt(Yuv444pFrame::U_PLANE, i*2);
		intensityAt(V_PLANE, i) = src.intensityAt(Yuv444pFrame::V_PLANE, i*2);
	}
	return *this;
}

Yuv422pFrame& Yuv422pFrame::operator=(Yuv420pFrame& const src) {
	resize(src.width(), src.height());
	copy(src.data(), src.data() + width()*height(), data());
	for (int y = 0; y < height(); y++) {
		for (int x = 0; x < width()/2; x++) {
			intensityAt(U_PLANE, x, y) = src.intensityAt(Yuv420pFrame::U_PLANE, x, y/2);
			intensityAt(V_PLANE, x, y) = src.intensityAt(Yuv420pFrame::V_PLANE, x, y/2);
		}
	}
	return *this;
}

Yuv422pFrame& Yuv422pFrame::operator=(GrayDoubleFrame& const src) {
	resize(src.width(), src.height());
	for (int i = 0; i < width()*height(); i++) {
		intensityAt(Y_PLANE, i) = static_cast<uint8_t>(src.intensityAt(i) * 0xFF);
	}
	for (int i = 0; i < (width()*height())/2; i++) {
		intensityAt(U_PLANE, i) = 0x80;
		intensityAt(V_PLANE, i) = 0x80;
	}
	return *this;
}

Yuv422pFrame& Yuv422pFrame::operator=(Gray16leFrame& const src) {
	resize(src.width(), src.height());
	for (int i = 0; i < width()*height(); i++) {
		intensityAt(Y_PLANE, i) = static_cast<uint8_t>(src.intensityAt(i) >> 8);
	}
	for (int i = 0; i < (width()*height())/2; i++) {
		intensityAt(U_PLANE, i) = 0x80;
		intensityAt(V_PLANE, i) = 0x80;
	}
	return *this;
}
