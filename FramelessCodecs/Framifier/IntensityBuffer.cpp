#include "IntensityBuffer.h"


IntensityBuffer::IntensityBuffer(istream &stream, size_t num_pixels) :
	buffer(num_pixels),
	stream(stream) {
}

void IntensityBuffer::read(PixelFire &pixel) {
	uint16_t dt;
	stream.read(reinterpret_cast<char*>(&pixel.i), sizeof(pixel.i));
	stream.read(reinterpret_cast<char*>(&pixel.d), sizeof(pixel.d));
	stream.read(reinterpret_cast<char*>(&dt),      sizeof(dt));
	pixel.dt = dt;
}

void IntensityBuffer::fillBuffer(index_t i) {
	while (buffer[i].empty() && stream.good()) {
		PixelFire pixel;
		read(pixel);
		buffer[pixel.i].emplace(pixel.d, pixel.dt);
	}
}

Intensity& IntensityBuffer::next(index_t i) {
	return buffer[i].front();
}

void IntensityBuffer::pop(index_t i) {
	buffer[i].pop();
}

bool IntensityBuffer::empty(index_t i) const {
	return buffer[i].empty();
}
