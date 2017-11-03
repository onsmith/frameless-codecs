#include "PixelFireStreamSink.h"

#include <cstdint>


PixelFireStreamSink::PixelFireStreamSink(ostream &stream) :
	stream(stream) {
}

void PixelFireStreamSink::write(PixelFire &pf) {
	uint16_t dt = pf.dt;
	stream.write(reinterpret_cast<const char*>(&pf.x), sizeof(pf.x));
	stream.write(reinterpret_cast<const char*>(&pf.y), sizeof(pf.y));
	stream.write(reinterpret_cast<const char*>(&pf.d), sizeof(pf.d));
	stream.write(reinterpret_cast<const char*>(&dt),   sizeof(dt));
}
