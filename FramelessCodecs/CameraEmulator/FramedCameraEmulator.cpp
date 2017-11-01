#include "FramedCameraEmulator.h"

#include "Frame/GrayDoubleFrame.h"

#include <fstream>
using std::istream;
using std::ostream;


FramedCameraEmulator::FramedCameraEmulator(int width, int height, int fps, int tps) :
	width(width),
	height(height),
	fps(fps),
	tps(tps),
	tpf(tps / fps) {
}

void FramedCameraEmulator::emulate(istream &input, ostream &output) const {
	// Initialize timestamp integer
	unsigned long int t = 0;

	// Pre-calculate number of pixels
	unsigned long int nop = width * height;

	// Initialize data frames
	GrayDoubleFrame intensity(width, height);
	GrayDoubleFrame target_light(width, height);
	GrayDoubleFrame accumulated_light(width, height);

	// Zero out accumulated light for each pixel
	for (int i = 0; i < nop; i++) {
		accumulated_light(i) = 0.0;
	}

	// Set initial light for each pixel
	for (int i = 0; i < nop; i++) {
		accumulated_light(i) = 0.0;
	}

	// Loop through frames
	int frame_count = 0;
	while (intensity.readFrom(input)) {
		frame_count++;

		// Loop through ticks (i) and pixels (j) within the frame
		for (int i = 0; i < tpf; i++, t++) {
			for (int j = 0; j < nop; j++) {
				accumulated_light(j) += intensity(j) / tps;
				if (accumulated_light(j) > target_light(j)) {
				}
			}
		}
	}
}
