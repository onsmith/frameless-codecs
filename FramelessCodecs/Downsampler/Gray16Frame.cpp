#include "Gray16Frame.h"


Gray16Frame::intensity_t* Gray16Frame::getData() {
	return data;
}


Gray16Frame::intensity_t* Gray16Frame::getLuma() {
	return data;
}


unsigned int Gray16Frame::getNumPixels() {
	return width * height;
}


size_t Gray16Frame::getDataLength() {
	return width * height;
}


Gray16Frame::intensity_t Gray16Frame::getIntensity(unsigned int i) {
	return data[i];
}


Gray16Frame::intensity_t Gray16Frame::getIntensity(unsigned int x, unsigned int y) {
	return data[y * width + x];
}


Gray16Frame::Gray16Frame(const unsigned int width, const unsigned int height) {
	this->width  = width;
	this->height = height;
	this->data   = new uint16_t[getDataLength()];
}


Gray16Frame::Gray16Frame(Gray16Frame &obj) {
	const unsigned int dataLength = getDataLength();
	width  = obj.width;
	height = obj.height;
	data   = new uint16_t[dataLength];
	for (unsigned int i = 0; i < dataLength; i++) {
		data[i] = obj.getIntensity(i);
	}
}


Gray16Frame::~Gray16Frame() {
	delete data;
}
