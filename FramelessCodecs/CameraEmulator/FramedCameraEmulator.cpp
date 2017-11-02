#include "FramedCameraEmulator.h"

#include "PixelTracker.h"
#include "Frame/GrayDoubleFrame.h"

#include <fstream>
using std::istream;
using std::ostream;

#include <vector>
using std::vector;


FramedCameraEmulator::FramedCameraEmulator(
	int width,
	int height,
	int ticks_per_second,
	int frames_per_second,
	Source<GrayDoubleFrame>& input,
	Sink<PixelFire>& output,
	DController& dController
) :
	tps(ticks_per_second),
	fps(frames_per_second),
	input(input),
	output(output),
	dController(dController),
	pixels(width*height),
	t(0),
	frame(width, height),
	tpf(ticks_per_second / frames_per_second) {
	initPixelTrackers();
}

void FramedCameraEmulator::initPixelTrackers() {
	for (int i = 0; i < numPixels(); i++) {
		PixelTracker pixel = pixels[i];
		pixel.x                 = (i % width());
		pixel.y                 = (i / width());
		pixel.d                 = dController.initD(pixel.x, pixel.y);
		pixel.t                 = 0;
		pixel.target_light      = static_cast<light_t>(1 << pixel.d);
		pixel.accumulated_light = 0.0;
	}
}

int FramedCameraEmulator::width() const {
	return frame.width();
};

int FramedCameraEmulator::height() const {
	return frame.height();
};

int FramedCameraEmulator::numPixels() const {
	return pixels.size();
};

void FramedCameraEmulator::emulateFrame() {
	// Read next frame from input
	input.read(frame);

	// Scale intensities by tick period
	for (int j = 0; j < numPixels(); j++) {
		frame(j) /= static_cast<light_t>(tps);
	}

	// Loop through ticks (i) and pixels (j),
	//   accumulating light and emitting pixel fires
	for (int i = 0; i < tpf; i++, t++) {
		for (int j = 0; j < numPixels(); j++) {
				PixelTracker pixel = pixels[j];
				pixel.accumulated_light += frame(j);
				if (pixel.accumulated_light > pixel.target_light) {
					unsigned long int dt = t - pixel.t;
					// emit pixel (pixel.x, pixel.y, pixel.d, dt)
					pixel.t = t;
					pixel.d = dController.nextD(pixel.x, pixel.y, pixel.d, dt);
					pixel.accumulated_light -= pixel.target_light;
					pixel.target_light = static_cast<double>(1 << pixel.d);
			}
		}
	}
}
