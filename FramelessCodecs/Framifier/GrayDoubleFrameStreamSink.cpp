#include "GrayDoubleFrameStreamSink.h"

#include <cstdint>


GrayDoubleFrameStreamSink::GrayDoubleFrameStreamSink(ostream &stream) :
	stream(stream) {
}

void GrayDoubleFrameStreamSink::write(GrayDoubleFrame &frame) {
	frame.writeTo(stream);
}
