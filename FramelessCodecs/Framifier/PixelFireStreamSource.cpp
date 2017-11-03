#include "PixelFireStreamSource.h"


PixelFireStreamSource::PixelFireStreamSource(istream &stream) :
	stream(stream) {
}

void PixelFireStreamSource::read(PixelFire &pixel) {
	uint16_t dt;
	stream.read(reinterpret_cast<char*>(&pixel.x), sizeof(pixel.x));
	stream.read(reinterpret_cast<char*>(&pixel.y), sizeof(pixel.y));
	stream.read(reinterpret_cast<char*>(&pixel.d), sizeof(pixel.d));
	stream.read(reinterpret_cast<char*>(&dt),      sizeof(dt));
	pixel.dt = dt;
}
