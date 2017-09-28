#include "Gray16Frame.h"



void Gray16Frame::initialize(const unsigned int width, const unsigned int height, const unsigned int index) {
	this->width  = width;
	this->height = height;
	this->index  = index;
	this->data   = new uint16_t[width * height];
}


Gray16Frame::Gray16Frame(const unsigned int width, const unsigned int height, const unsigned int index) {
	this->width  = width;
	this->height = height;
	this->index  = index;
	this->data   = new uint16_t[width * height];
}


Gray16Frame::Gray16Frame(const unsigned int width, const unsigned int height) {

}


Gray16Frame::~Gray16Frame() {
}
