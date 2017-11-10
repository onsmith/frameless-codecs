#include "IntensityBuffer.h"


IntensityBuffer::IntensityBuffer(istream &stream, size_t num_pixels) :
	buffer(num_pixels),
	stream(stream) {
}

void IntensityBuffer::fillBuffer(index_t i) {
	while (buffer[i].empty() && stream.good()) {
		PixelFire pixel;
		pixel.readFrom(stream);
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
