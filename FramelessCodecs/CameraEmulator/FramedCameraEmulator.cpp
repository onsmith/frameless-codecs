#include "FramedCameraEmulator.h"

#include "PixelTracker.h"
#include "Frame/GrayDoubleFrame.h"

#include <vector>
using std::vector;

#include <queue>
using std::priority_queue;

#include <iostream>
using std::istream;

#include <cmath>


FramedCameraEmulator::FramedCameraEmulator(istream& input, ostream& output, int width, int height, int fps) :
	t(0),                      // Time tick counter
	fps(fps),                  // Frames per second
	dControl(5),               // Constant D controller
	input(input),              // Input data source
	//output(output),            // Output data source
	pixels(width*height),      // Array of PixelTracker objects
	frame(width, height),      // GrayDoubleFrame input buffer object
	tpf(tps / fps) {           // Ticks per frame
	initializePixelTrackers();
}

void FramedCameraEmulator::initializePixelTrackers() {
	for (int i = 0; i < numPixels(); i++) {
		PixelTracker &pixel = pixels[i];
		pixel.x                 = (i % width());
		pixel.y                 = (i / width());
		pixel.d                 = dControl.initD(pixel.x, pixel.y);
		pixel.last_fire_time    = 0;
		pixel.next_fire_time    = 0;
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

struct LargestFireTimeFirst {
	bool operator()(const PixelTracker* const l, const PixelTracker* const r) {
		return l->next_fire_time < r->next_fire_time;
	};
};

void FramedCameraEmulator::emulateFrame() {
	// Read next frame from input
	input.read(frame);

	// Scale intensities
	for (int i = 0; i < numPixels(); i++) {
		frame(i) *= (0x1 << 14); // Scale up values
		frame(i) += 1;           // Zero intensity not allowed
		frame(i) /= tps;         // Make intensity independent of tick length
	}

	// Keep track of start and end timestamps for this frame
	timestamp_t frame_start_time = t;
	timestamp_t frame_end_time   = frame_start_time + tpf;

	// Create queue to store pixels that fire during this frame
	priority_queue<PixelTracker*, vector<PixelTracker*>, LargestFireTimeFirst> queue;

	// Add pixels that will fire during this frame to the priority queue
	for (int i=0; i < numPixels(); i++) {
		PixelTracker &pixel = pixels[i];
		bool pixel_will_fire = accumulateLight(pixel, frame(i), tpf);
		if (pixel_will_fire) {
			queue.push(&pixel);
		}
	}

	// Loop through priority queue and fire pixels
	while (!queue.empty()) {
		PixelTracker &pixel = *queue.top();
		queue.pop();
		t = pixel.next_fire_time;
		timestamp_t light_accumulation_start_time = (t > frame_start_time) ? t : frame_start_time;
		timestamp_t light_accumulation_period = t - light_accumulation_start_time;
		pixel.accumulated_light += frame(pixel.x, pixel.y) * light_accumulation_period;
		firePixel(pixel);
		bool pixel_will_fire_again = accumulateLight(pixel, frame(pixel.x, pixel.y), frame_end_time - t);
		if (pixel_will_fire_again) {
			queue.push(&pixel);
		}
	}

	// Finished the frame, so update t
	t = frame_end_time;
}

void FramedCameraEmulator::firePixel(PixelTracker& pixel) {
	timedelta_t dt = pixel.next_fire_time - pixel.last_fire_time;
	PixelFire pf(pixel.x, pixel.y, pixel.d, dt);
	output.write(pf);
	pixel.last_fire_time = pixel.next_fire_time;
	pixel.d = dControl.nextD(pixel.x, pixel.y, pixel.d, dt);
	pixel.accumulated_light -= pixel.target_light;
	pixel.target_light = (0x1 << pixel.d);
}

bool FramedCameraEmulator::accumulateLight(PixelTracker& pixel, light_t light_unit, timedelta_t period) {
	light_t light_accumulated_by_end_of_period = pixel.accumulated_light + light_unit * period;
		if (light_accumulated_by_end_of_period >= pixel.target_light) {
			light_t light_needed_to_fire = pixel.target_light - pixel.accumulated_light;
			timedelta_t timesteps_until_fire = ceil(light_needed_to_fire / light_unit);
			pixel.next_fire_time = t + timesteps_until_fire;
			pixel.accumulated_light += light_unit * timesteps_until_fire;
			return true;
		} else {
			pixel.accumulated_light = light_accumulated_by_end_of_period;
			return false;
		}
}
