#include "PixelFireStreamSink.h"


PixelFireStreamSink::PixelFireStreamSink(ostream &stream) :
	stream(stream) {
}

void PixelFireStreamSink::write(PixelFire &pf) {
	stream.write(reinterpret_cast<char*>(&pf.x),  sizeof(pf.x));
	stream.write(reinterpret_cast<char*>(&pf.y),  sizeof(pf.y));
	stream.write(reinterpret_cast<char*>(&pf.d),  sizeof(pf.d));
	stream.write(reinterpret_cast<char*>(&pf.dt), sizeof(pf.dt));
}
