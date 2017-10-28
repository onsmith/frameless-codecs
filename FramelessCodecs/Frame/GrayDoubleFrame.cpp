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
