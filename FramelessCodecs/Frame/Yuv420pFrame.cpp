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

uint8_t& Yuv420pFrame::intensityAt(int i) const {
	return data()[i];
}

uint8_t& Yuv420pFrame::intensityAt(int plane, int i) const {
	return intensityAt(offsets_[plane] + i);
}

uint8_t& Yuv420pFrame::intensityAt(int plane, int x, int y) const {
	return intensityAt(plane, y * strides_[plane] + x);
}
