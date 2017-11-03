#include "FramedCameraEmulator.h"

#include "PixelTracker.h"
#include "Frame/GrayDoubleFrame.h"

#include <vector>
using std::vector;

#include <iostream>
using std::istream;


#define CONSTANT_D 8
#define INITIAL_D  8
#define TARGET_DT  8


FramedCameraEmulator::FramedCameraEmulator(istream& input, ostream& output, int width, int height, int fps) :
	t(0),                           // Time tick counter
	fps(fps),                       // Frames per second
	dControl(CONSTANT_D),           // Constant D controller
	//dControl(INITIAL_D, TARGET_DT), // Target frame rate D controller
	input(input),                   // Input data source
	output(output),                 // Output data source
	pixels(width*height),           // Array of PixelTracker objects
	frame(width, height),           // GrayDoubleFrame input buffer object
	tpf(tps / fps) {                // Ticks per frame
	initializePixelTrackers();
}

void FramedCameraEmulator::initializePixelTrackers() {
	for (int i = 0; i < numPixels(); i++) {
		PixelTracker &pixel = pixels[i];
		pixel.x                 = (i % width());
		pixel.y                 = (i / width());
		pixel.d                 = dControl.initD(pixel.x, pixel.y);
		pixel.last_fire_time    = 0;
		pixel.target_light      = static_cast<light_t>(1 << pixel.d);
		pixel.accumulated_light = 0.0;
	}
}

int FramedCameraEmulator::width() const {
	return frame.width();
}

int FramedCameraEmulator::height() const {
	return frame.height();
}

size_t FramedCameraEmulator::numPixels() const {
	return pixels.size();
}

void FramedCameraEmulator::emulateFrame() {
	// Read next frame from input
	input.read(frame);

	// Scale intensities
	for (int j = 0; j < numPixels(); j++) {
		frame(j) *= (0x1 << 14); // Arbitrarily scale values
		frame(j) += 1;           // Zero intensity pixels are disallowed
		frame(j) /= tps;         // Turn intensity into the amount of light gathered per tick
	}

	// Loop through ticks (i) over time and pixels (j) over space, accumulating
	//   light and emitting pixel fires as necessary
	for (int i = 0; i < tpf; i++, t++) {
		for (int j = 0; j < numPixels(); j++) {
			PixelTracker &pixel = pixels[j];
			pixel.accumulated_light += frame(j);
			if (pixel.accumulated_light >= pixel.target_light) {
				firePixel(pixel);
			}
		}
	}
}

void FramedCameraEmulator::firePixel(PixelTracker& pixel) {
	timedelta_t dt = t - pixel.last_fire_time;
	PixelFire pf(pixel.x, pixel.y, pixel.d, dt);
	output.write(pf);
	pixel.last_fire_time = t;
	pixel.d = dControl.nextD(pixel.x, pixel.y, pixel.d, dt);
	pixel.accumulated_light -= pixel.target_light;
	pixel.target_light = (0x1 << pixel.d);
}
