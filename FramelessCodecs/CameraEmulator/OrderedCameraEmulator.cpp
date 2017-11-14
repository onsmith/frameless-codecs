#include "OrderedCameraEmulator.h"

#include "PixelFire.h"
#include "PixelTracker.h"
#include "Frame/GrayDoubleFrame.h"

#include <iostream>
using std::endl;


#define TICKS_PER_FRAME 40


OrderedCameraEmulator::OrderedCameraEmulator(
	istream& input,
	ostream& output,
	pixel_t width,
	pixel_t height,
	time_t fps
) :
	source(input, width, height, fps, TICKS_PER_FRAME),
	output(output),
	pixels(width*height),
	buffer(TICKS_PER_FRAME),
	dControl(10)
	//dControl(10, 38)
	//dControl(
	//	6,  16,  // Initial d and target dt value for ROI
	//	12, 160, // Initial d and target dt value for background
	//	width,   // Width of video
	//	200, 30, // (x, y) coordinates of min point of ROI bounding box
	//	440, 355 // (x, y) coordinates of max point of ROI bounding box
	//)
{
	initializePixelTrackers();
	source.nextFrame();
}

void OrderedCameraEmulator::initializePixelTrackers() {
	for (int i = 0; i < numPixels(); i++) {
		PixelTracker &pixel = pixels[i];
		pixel.i = i;
		pixel.updateDecimation(dControl.initD(i));
	}
}

void OrderedCameraEmulator::writeBinary(const PixelFire &pixel) {
	pixel.writeBinaryTo(output);
}

void OrderedCameraEmulator::writeText(const PixelFire &pixel) {
	pixel.writeTextTo(output);
}

int OrderedCameraEmulator::width() const {
	return source.width();
}

int OrderedCameraEmulator::height() const {
	return source.height();
}

size_t OrderedCameraEmulator::numPixels() const {
	return pixels.size();
}

void OrderedCameraEmulator::emulateFrame() {
	// Loop through pixels and emit events
	const time_t time_frame_begins = source.ticksPerFrame() *  currentFrame;
	const time_t time_frame_ends   = source.ticksPerFrame() * (currentFrame + 1);
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

	// Write pixels fired this frame to the output stream
	flushBuffer();
	
	// Move to next frame.
	source.nextFrame();
	currentFrame++;
}

void OrderedCameraEmulator::firePixel(PixelTracker& pixel, time_t fire_time) {
	while (pixel.readyToFire()) {
		time_t dt = fire_time - pixel.last_fire_time;
		if (dt > 0) {
			buffer[(fire_time - 1) % TICKS_PER_FRAME].emplace_back(pixel.i, pixel.d, dt);
		}
		pixel.fire(fire_time);
		pixel.updateDecimation(dControl.nextD(pixel.i, pixel.d, dt));
	}
}

void OrderedCameraEmulator::flushBuffer() {
	for (int i = 0; i < buffer.size(); i++) {
		for (int j = 0; j < buffer[i].size(); j++) {
			writeBinary(buffer[i][j]);
			//writeText(buffer[i][j]);
		}
		buffer[i].clear();
	}
}
