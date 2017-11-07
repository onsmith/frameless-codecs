#include "OrderedPixelFireStreamSource.h"


int OrderedPixelFireStreamSource::index(const PixelFire& pixel) const {
	return stride * pixel.y + pixel.x;
}

OrderedPixelFireStreamSource::OrderedPixelFireStreamSource(istream &stream, int width, int height) :
	buffer(width * height),
	stride(width),
	stream(stream),
	bufferSize(0) {
}

void OrderedPixelFireStreamSource::read(PixelFire &pixel) {
	uint16_t dt;
	stream.read(reinterpret_cast<char*>(&pixel.x), sizeof(pixel.x));
	stream.read(reinterpret_cast<char*>(&pixel.y), sizeof(pixel.y));
	stream.read(reinterpret_cast<char*>(&pixel.d), sizeof(pixel.d));
	stream.read(reinterpret_cast<char*>(&dt),      sizeof(dt));
	pixel.dt = dt;
}

void OrderedPixelFireStreamSource::fillBuffer(int i) {
	while (buffer[i].empty() && stream.good()) {
		PixelFire pixel;
		read(pixel);
		buffer[index(pixel)].emplace(pixel.d, pixel.dt);
		bufferSize++;
	}
}

Intensity& OrderedPixelFireStreamSource::next(int i) {
	return buffer[i].front();
}

void OrderedPixelFireStreamSource::pop(int i) {
	buffer[i].pop();
	bufferSize--;
}

bool OrderedPixelFireStreamSource::empty(int i) const {
	return buffer[i].empty();
}

int OrderedPixelFireStreamSource::size() const {
	return bufferSize;
}
