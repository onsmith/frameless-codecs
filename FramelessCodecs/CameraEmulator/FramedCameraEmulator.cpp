#include "FramedCameraEmulator.h"

#include "PixelTracker.h"
#include "Frame/GrayDoubleFrame.h"

#include <vector>
using std::vector;

#include <iostream>
using std::istream;
using std::cout;
using std::endl;


#define CONSTANT_D 5
#define INITIAL_D  5
//#define TARGET_DT  5


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

	// Loop through pixels and emit events
	timestamp_t const frame_end_time = t + tpf;
	for (int i = 0; i < numPixels(); i++) {
		PixelTracker &pixel = pixels[i];
		timestamp_t current_time = t;
		timestamp_t next_fire_time = current_time + timestepsUntilNextFire(pixel, frame(i));
		while (next_fire_time <= frame_end_time) {
			pixel.accumulated_light += frame(i) * (next_fire_time - current_time);
			firePixel(pixel, next_fire_time);
			current_time = next_fire_time;
			next_fire_time += timestepsUntilNextFire(pixel, frame(i));
		}
		pixel.accumulated_light += frame(i) * (frame_end_time - current_time);
	}

	// Move timestamp forward
	t = frame_end_time;
}

timedelta_t FramedCameraEmulator::timestepsUntilNextFire(const PixelTracker& pixel, light_t light_accumulated_per_timestep) const {
	light_t light_needed_to_fire = pixel.target_light - pixel.accumulated_light;
	return ceil(light_needed_to_fire / light_accumulated_per_timestep);
}

void FramedCameraEmulator::firePixel(PixelTracker& pixel, timestamp_t fire_time) {
	timedelta_t dt = fire_time - pixel.last_fire_time;
	output.write(PixelFire(pixel.x, pixel.y, pixel.d, dt));
	pixel.last_fire_time = fire_time;
	pixel.accumulated_light -= pixel.target_light;
	pixel.d = dControl.nextD(pixel.x, pixel.y, pixel.d, dt);
	pixel.target_light = (0x1 << pixel.d);
}
