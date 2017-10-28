#include "Frame.h"


Frame::Frame(int width, int height) :
	width_(width),
	height_(height) {
}

void Frame::resize(int width, int height) {
	width_  = width;
	height_ = height;
}

int Frame::width() const {
	return width_;
}

int Frame::height() const {
	return height_;
}
