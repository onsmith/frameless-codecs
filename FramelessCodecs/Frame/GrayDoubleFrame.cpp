#include "GrayDoubleFrame.h"


GrayDoubleFrame::GrayDoubleFrame(int width, int height) :
	DataFrame(width, height, width*height) {
}

void GrayDoubleFrame::resize(int width, int height) {
	DataFrame::resize(width, height, width*height);
}

double& GrayDoubleFrame::intensityAt(int i) {
	return data()[i];
}

double& GrayDoubleFrame::intensityAt(int x, int y) {
	return intensityAt(y*width() + x);
}

GrayDoubleFrame& GrayDoubleFrame::operator=(Frame& src) {
	resize(src.width(), src.height());
	for (int y = 0; y < height(); y++) {
		for (int x = 0; x < width(); x++) {
			intensityAt(x, y) = src.getIntensityAsDouble(Y_PLANE, x, y);
		}
	}
	return *this;
}

uint8_t GrayDoubleFrame::getIntensityAsByte(int plane, int x, int y) {
	return (plane == Y_PLANE) ? static_cast<uint8_t>(intensityAt(x, y) * 0xFF) : 0x80;
}

uint16_t GrayDoubleFrame::getIntensityAs16Bits(int plane, int x, int y) {
	return (plane == Y_PLANE) ? static_cast<uint16_t>(intensityAt(x, y) * 0xFFFF) : 0x8000;
}

double GrayDoubleFrame::getIntensityAsDouble(int plane, int x, int y) {
	return (plane == Y_PLANE) ? intensityAt(x, y) : 0.5;
}
