#include "Gray16leFrame.h"

#include <cstdint>


Gray16leFrame::Gray16leFrame(int width, int height) :
	DataFrame(width, height, width*height) {
}

void Gray16leFrame::resize(int width, int height) {
	DataFrame::resize(width, height, width*height);
}

uint16_t& Gray16leFrame::intensityAt(int i) const {
	return data()[i];
}

uint16_t& Gray16leFrame::intensityAt(int x, int y) const {
	return intensityAt(y*width() + x);
}

uint16_t& Gray16leFrame::intensityAt(int _, int x, int y) const {
	return intensityAt(x, y);
}
