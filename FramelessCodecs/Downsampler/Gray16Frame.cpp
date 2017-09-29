#include "Gray16Frame.h"

#include <assert.h>


Gray16Frame::intensity_t* Gray16Frame::getData() {
	return data;
}


Gray16Frame::intensity_t* Gray16Frame::getLuma() {
	return data;
}


int Gray16Frame::getNumPixels() const {
	return width * height;
}


size_t Gray16Frame::getDataLength() const {
	return width * height;
}


Gray16Frame::intensity_t Gray16Frame::getIntensity(int i) const {
	return data[i];
}


Gray16Frame::intensity_t Gray16Frame::getIntensity(int x, int y) const {
	return data[y * width + x];
}


Gray16Frame::Gray16Frame(const int width, const int height) {
	assert(width  > 0);
	assert(height > 0);
	this->width  = width;
	this->height = height;
	this->data   = new uint16_t[getDataLength()];
}


Gray16Frame::Gray16Frame(const Gray16Frame &obj) {
	const int dataLength = getDataLength();
	width  = obj.width;
	height = obj.height;
	data   = new uint16_t[dataLength];
	for (int i = 0; i < dataLength; i++) {
		data[i] = obj.getIntensity(i);
	}
}


Gray16Frame::~Gray16Frame() {
	delete data;
}
