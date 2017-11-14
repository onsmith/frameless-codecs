#include "OrderedFramifier.h"
#include "FramelessIntensity.h"

#include <iostream>
using std::cerr;
using std::endl;


OrderedFramifier::OrderedFramifier(
	istream &input,
	ostream &output,
	size_t width,
	size_t height,
	int fps
) :
	input(input),
	output(output),
	nextChangeTime(width * height, 0),
	frame(width, height),
	fps(fps),
	tpf(tps / fps) {
	pixel.readFrom(input);
}

void OrderedFramifier::framifyPixelFires() {
	// Calculate the timestamp at the end of this frame
	time_t const frame_end_time = tpf*(++frameNumber);

	// Read values from the input stream until the current frame is over
	while (input.good() && nextChangeTime[pixel.i] <= frame_end_time) {
		frame(pixel.i) = FramelessIntensity::toDouble(pixel.d, pixel.dt, tps);
		nextChangeTime[pixel.i] += pixel.dt;
		pixel.readFrom(input);
	}

	// Write frame to output
	frame.writeTo(output);
}

size_t OrderedFramifier::width() const {
	return frame.width();
}

size_t OrderedFramifier::height() const {
	return frame.height();
}

size_t OrderedFramifier::numPixels() const {
	return nextChangeTime.size();
}
