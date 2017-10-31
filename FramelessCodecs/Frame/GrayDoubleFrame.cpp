#include "GrayDoubleFrame.h"


GrayDoubleFrame::GrayDoubleFrame(int width, int height) :
	DataFrame(width, height, width*height) {
}

void GrayDoubleFrame::resize(int width, int height) {
	DataFrame::resize(width, height, width*height);
}

double& GrayDoubleFrame::intensityAt(int i) const {
	return data()[i];
}

double& GrayDoubleFrame::intensityAt(int x, int y) const {
	return intensityAt(y*width() + x);
}

double& GrayDoubleFrame::intensityAt(int _, int x, int y) const {
	return intensityAt(x, y);
}

GrayDoubleFrame& GrayDoubleFrame::operator=(Frame& const src) {
	resize(src.width(), src.height());
	for (int y = 0; y < height(); y++) {
		for (int x = 0; x < width(); x++) {
			intensityAt(LUMA_PLANE, x, y) = src.getIntensityAsDouble(Y_PLANE, x, y);
		}
	}
	return *this;
}

uint8_t GrayDoubleFrame::getIntensityAsByte(int plane, int i) const {
	return (plane == 0) ? static_cast<uint8_t>(intensityAt(i) * 0xFF) : 0x80;
}

uint8_t GrayDoubleFrame::getIntensityAsByte(int plane, int x, int y) const {
	return (plane == 0) ? static_cast<uint8_t>(intensityAt(x, y) * 0xFF) : 0x80;
}

uint16_t GrayDoubleFrame::getIntensityAs16Bits(int plane, int i) const {
	return static_cast<uint16_t>(intensityAt(plane, i) * 0xFFFF);
}

uint16_t GrayDoubleFrame::getIntensityAs16Bits(int plane, int x, int y) const {
	return static_cast<uint16_t>(intensityAt(plane, x, y) * 0xFFFF);
}

double GrayDoubleFrame::getIntensityAsDouble(int plane, int i) const {
	return intensityAt(plane, i);
}

double GrayDoubleFrame::getIntensityAsDouble(int plane, int x, int y) const {
	return intensityAt(plane, x, y);
}
