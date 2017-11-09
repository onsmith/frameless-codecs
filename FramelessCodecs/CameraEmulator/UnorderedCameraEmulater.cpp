#include "UnorderedCameraEmulator.h"

#include "PixelFire.h"
#include "PixelTracker.h"
#include "Frame/GrayDoubleFrame.h"

#include <iostream>
using std::endl;


#define INTENSITY_MIN   1
#define INTENSITY_RANGE (0x1 << 14)


UnorderedCameraEmulator::UnorderedCameraEmulator(
	istream& input,
	ostream& output,
	int width,
	int height,
	int fps
) :
	fps(fps),                       // Frames per second
	input(input),                   // Input data source
	output(output),                 // Output data source
	pixels(width*height),           // Array of PixelTracker objects
	frame(width, height),           // GrayDoubleFrame input buffer object
	tpf(tps / fps)                  // Ticks per frame
{
	initializePixelTrackers();
}

void UnorderedCameraEmulator::initializePixelTrackers() {
	for (int i = 0; i < numPixels(); i++) {
		PixelTracker &pixel = pixels[i];
		pixel.i                 = i;
		pixel.d                 = dControl.initD(i);
		pixel.last_fire_time    = 0;
		pixel.target_light      = static_cast<light_t>(0x1 << pixel.d);
		pixel.accumulated_light = 0.0;
	}
}

inline void UnorderedCameraEmulator::writeBinary(const PixelFire &pixel) {
	uint16_t dt = pixel.dt;
	output.write(reinterpret_cast<const char*>(&pixel.i), sizeof(pixel.i));
	output.write(reinterpret_cast<const char*>(&pixel.d), sizeof(pixel.d));
	output.write(reinterpret_cast<const char*>(&dt     ), sizeof(dt));
}

void UnorderedCameraEmulator::writeText(const PixelFire &pixel) {
	output
		<< "("
		<< static_cast<int>(pixel.i) << ", "
		<< static_cast<int>(pixel.d) << ", "
		<< static_cast<int>(pixel.dt)
		<< ")" << endl;
}

int UnorderedCameraEmulator::width() const {
	return frame.width();
}

int UnorderedCameraEmulator::height() const {
	return frame.height();
}

size_t UnorderedCameraEmulator::numPixels() const {
	return pixels.size();
}

void UnorderedCameraEmulator::emulateFrame() {
	// Read frame from input
	frame.readFrom(input);

	// Scale intensities
	for (int i = 0; i < numPixels(); i++) {
		frame(i) = scaleIntensity(frame(i));
	}

	// Loop through pixels and emit events
	timestamp_t const frame_begin_time = tpf*frameNumber;
	timestamp_t const frame_end_time   = tpf*(frameNumber + 1);
	for (int i = 0; i < numPixels(); i++) {
		PixelTracker &pixel = pixels[i];
		timestamp_t current_time = frame_begin_time;
		while (true) {
			const timestamp_t early_fire_time = pixel.last_fire_time + dtMax;
			const timestamp_t next_fire_time  = current_time + timestepsUntilNextFire(pixel, frame(i));
			// Case 1: Pixel fires normally before frame ends
			if (next_fire_time <= frame_end_time && next_fire_time <= early_fire_time) {
				pixel.accumulated_light += frame(i) * (next_fire_time - current_time);
				current_time = next_fire_time;
				firePixel(pixel, current_time);
			// Case 2: Pixel fires prematurely before frame ends
			} else if (early_fire_time <= frame_end_time && early_fire_time < next_fire_time) {
				pixel.accumulated_light = pixel.target_light;
				current_time = early_fire_time;
				firePixel(pixel, current_time);
			// Case 3: Pixel does not fire before frame ends
			} else {
				pixel.accumulated_light += frame(i) * (frame_end_time - current_time);
				break;
			}
		}
	}

	// Move to next frame
	frameNumber++;
}

timedelta_t UnorderedCameraEmulator::timestepsUntilNextFire(const PixelTracker& pixel, light_t light_accumulated_per_timestep) const {
	light_t light_needed_to_fire = pixel.target_light - pixel.accumulated_light;
	return ceil(light_needed_to_fire / light_accumulated_per_timestep);
}

void UnorderedCameraEmulator::firePixel(PixelTracker& pixel, timestamp_t fire_time) {
	while (pixel.accumulated_light >= pixel.target_light) {
		timedelta_t dt = fire_time - pixel.last_fire_time;
		if (dt > 0) {
			writeBinary(PixelFire(pixel.i, pixel.d, dt));
			// writeText(PixelFire(pixel.i, pixel.d, dt)); // DEBUG
		}
		pixel.last_fire_time = fire_time;
		pixel.accumulated_light -= pixel.target_light;
		pixel.d = dControl.nextD(pixel.i, pixel.d, dt);
		pixel.target_light = (0x1 << pixel.d);
	}
}

double UnorderedCameraEmulator::scaleIntensity(double intensity) const {
	intensity *= INTENSITY_RANGE;
	intensity += INTENSITY_MIN;
	intensity /= tps;
	return intensity;
}
