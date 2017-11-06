#include "FramelessStreamFramifier.h"

#include <iostream>
using std::cerr;
using std::endl;


int FramelessStreamFramifier::width() const {
	return frame.width();
}

int FramelessStreamFramifier::height() const {
	return frame.height();
}

size_t FramelessStreamFramifier::numPixels() const {
	return width() * height();
}

double FramelessStreamFramifier::computeIntensity(const Intensity &pixel) {
	return static_cast<double>(0x1 << pixel.d) / static_cast<double>(pixel.dt);
}

FramelessStreamFramifier::FramelessStreamFramifier(istream &input, ostream &output, int width, int height, int fps) :
	input(input, width, height),
	output(output),
	lastFireTimes(width * height, 0),
	frame(width, height),
	fps(fps),
	tpf(tps / fps) {
}

void FramelessStreamFramifier::framifyPixelFires() {
	// Update every pixel in the frame
	const timestamp_t time_frame_end = t + tpf;
	for (int i = 0; i < numPixels(); i++) {
		while (lastFireTimes[i] < time_frame_end) {
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

	// Write frame to output and move timestamp forward
	output.write(frame);
	t += tpf;
}
