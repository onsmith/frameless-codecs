#include "UnorderedCameraEmulator.h"

#include "PixelFire.h"
#include "PixelTracker.h"
#include "Frame/GrayDoubleFrame.h"

#include <iostream>
using std::endl;


#define TICKS_PER_FRAME 40


UnorderedCameraEmulator::UnorderedCameraEmulator(
	istream& input,
	ostream& output,
	pixel_t width,
	pixel_t height,
	time_t fps
) :
	source(input, width, height, fps, TICKS_PER_FRAME),
	output(output),
	pixels(width*height) {
	initializePixelTrackers();
}

void UnorderedCameraEmulator::initializePixelTrackers() {
	for (int i = 0; i < numPixels(); i++) {
		PixelTracker &pixel = pixels[i];
		pixel.i = i;
		pixel.updateDecimation(dControl.initD(i));
	}
}

inline void UnorderedCameraEmulator::writeBinary(const PixelFire &pixel) {
	pixel.writeBinaryTo(output);
}

void UnorderedCameraEmulator::writeText(const PixelFire &pixel) {
	pixel.writeTextTo(output);
}

int UnorderedCameraEmulator::width() const {
	return source.width();
}

int UnorderedCameraEmulator::height() const {
	return source.height();
}

size_t UnorderedCameraEmulator::numPixels() const {
	return pixels.size();
}

void UnorderedCameraEmulator::emulateFrame() {
	// Load next frame from LightSource.
	source.nextFrame();
	currentFrame++;

	// Loop through pixels and emit events
	const time_t time_frame_begins = source.ticksPerFrame() * (currentFrame - 1);
	const time_t time_frame_ends   = source.ticksPerFrame() *  currentFrame;
	for (int i = 0; i < numPixels(); i++) {
		PixelTracker &pixel = pixels[i];
		time_t current_time = time_frame_begins;
		while (true) {
			time_t next_fire_time = current_time +
				source.timeToAccumulateLight(pixel.i, pixel.lightDeficit(), current_time - time_frame_begins);
			time_t early_fire_time = pixel.last_fire_time + DT_MAX;
			// Case 1: Pixel fires normally before frame ends
			if (next_fire_time <= time_frame_ends && next_fire_time <= early_fire_time) {
				pixel.accumulated_light +=
					source.accumulateLight(pixel.i, current_time - time_frame_begins, next_fire_time - current_time);
				current_time = next_fire_time;
				firePixel(pixel, current_time);
			// Case 2: Pixel fires prematurely before frame ends
			} else if (early_fire_time <= time_frame_ends && early_fire_time < next_fire_time) {
				pixel.accumulated_light = pixel.target_light;
				current_time = early_fire_time;
				firePixel(pixel, current_time);
			// Case 3: Pixel does not fire before frame ends
			} else {
				pixel.accumulated_light +=
					source.accumulateLight(pixel.i, current_time - time_frame_begins, time_frame_ends - current_time);
				break;
			}
		}
	}
}

void UnorderedCameraEmulator::firePixel(PixelTracker& pixel, time_t fire_time) {
	while (pixel.readyToFire()) {
		time_t dt = fire_time - pixel.last_fire_time;
		if (dt > 0) {
			writeBinary(PixelFire(pixel.i, pixel.d, dt));
			//writeText(PixelFire(pixel.i, pixel.d, dt)); // DEBUG
		}
		pixel.fire(fire_time);
		pixel.updateDecimation(dControl.nextD(pixel.i, pixel.d, dt));
	}
}
