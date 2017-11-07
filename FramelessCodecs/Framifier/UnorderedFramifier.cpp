#include "UnorderedFramifier.h"

#include <iostream>
using std::cerr;
using std::endl;


UnorderedFramifier::UnorderedFramifier(
	istream &input,
	ostream &output,
	size_t width,
	size_t height,
	int fps
) :
	input(input, width * height),
	output(output),
	lastFireTimes(width * height, 0),
	frame(width, height),
	fps(fps),
	tpf(tps / fps) {
}

void UnorderedFramifier::framifyPixelFires() {
	// Update every pixel in the frame
	timestamp_t const frame_begin_time = tpf*frameNumber;
	timestamp_t const frame_end_time   = tpf*(frameNumber + 1);
	for (int i = 0; i < numPixels(); i++) {
		while (lastFireTimes[i] < frame_end_time) {
			input.fillBuffer(i);
			if (input.empty(i)) {
				cerr << "Warning! No more intensity data for pixel " << i << "." << endl;
				break;
			}
			Intensity &pixel = input.next(i);
			frame(i) = computeIntensity(pixel);
			lastFireTimes[i] += pixel.dt;
			input.pop(i);
		}
	}

	// Write frame to output and move to next frame
	frame.writeTo(output);
	frameNumber++;
}

double UnorderedFramifier::computeIntensity(const Intensity &pixel) const {
	// TODO: Scale according to tps and/or desired window
	return static_cast<double>(0x1 << pixel.d) / static_cast<double>(pixel.dt);
}

size_t UnorderedFramifier::width() const {
	return frame.width();
}

size_t UnorderedFramifier::height() const {
	return frame.height();
}

size_t UnorderedFramifier::numPixels() const {
	return lastFireTimes.size();
}
