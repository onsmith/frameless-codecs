#include "GrayDoubleFrameStreamSource.h"


GrayDoubleFrameStreamSource::GrayDoubleFrameStreamSource(istream &stream) :
	stream(stream) {
}

void GrayDoubleFrameStreamSource::read(GrayDoubleFrame &frame) {
	frame.readFrom(stream);
}
