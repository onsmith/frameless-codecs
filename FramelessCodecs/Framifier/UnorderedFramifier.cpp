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
	nextFireTime(width * height, 0),
	frame(width, height),
	fps(fps),
	tpf(tps / fps)
{
	initializeBuffer();
}

void UnorderedFramifier::initializeBuffer() {
	for (int i = 0; i < numPixels(); i++) {
		input.fillBuffer(i);
		if (!input.empty(i)) {
			nextFireTime[i] = input.next(i).dt;
		}
	}
};

void UnorderedFramifier::framifyPixelFires() {
	// Update every pixel in the frame
	timestamp_t const frame_begin_time = tpf*frameNumber;
	timestamp_t const frame_end_time   = tpf*(frameNumber + 1);
	for (int i = 0; i < numPixels(); i++) {
		while (!input.empty(i) && nextFireTime[i] <= frame_end_time) {
			Intensity &pixel = input.next(i);
			frame(i) = computeIntensity(pixel);
			input.pop(i);
			input.fillBuffer(i);
			if (!input.empty(i)) {
				nextFireTime[i] += input.next(i).dt;
			}
		}
	}

	// Write frame to output and move to next frame
	frame.writeTo(output);
	frameNumber++;
}

double UnorderedFramifier::computeIntensity(const Intensity &pixel) const {
	double intensity = (static_cast<double>(0x1 << pixel.d) / pixel.dt) * tps;
	//intensity -= 1;
	intensity /= 50000;
	return intensity;
}

size_t UnorderedFramifier::width() const {
	return frame.width();
}

size_t UnorderedFramifier::height() const {
	return frame.height();
}

size_t UnorderedFramifier::numPixels() const {
	return nextFireTime.size();
}
