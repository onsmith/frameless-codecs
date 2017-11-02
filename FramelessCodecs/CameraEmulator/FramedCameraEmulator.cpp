#include "FramedCameraEmulator.h"

#include "PixelTracker.h"
#include "Frame/GrayDoubleFrame.h"

#include <fstream>
using std::istream;
using std::ostream;

#include <vector>
using std::vector;


FramedCameraEmulator::FramedCameraEmulator(int width, int height, int fps, int tps) :
	width(width),
	height(height),
	fps(fps),
	tps(tps),
	tpf(tps / fps) {
}


int FramedCameraEmulator::emulate(istream &input, ostream &output) const {
	// Initialize timestamp integer
	unsigned long int t = 0;

	// Pre-calculate number of pixels
	long int numPixels = width * height;

	// Stores, for each pixel, the amount of light gathered during a single tick
	GrayDoubleFrame light_units(width, height);

	// Tracks information about each pixel
	vector<PixelTracker> pixels(numPixels);

	// Initialize pixel tracker objects
	for (int i = 0; i < numPixels; i++) {
		PixelTracker pixel = pixels[i];
		pixel.x                 = (i % width);
		pixel.y                 = (i / width);
		pixel.d                 = dController.initD(pixel.x, pixel.y);
		pixel.t                 = 0;
		pixel.target_light      = static_cast<double>(1 << pixel.d);
		pixel.accumulated_light = 0.0;
	}

	// Loop through frames
	int frame_count = 0;
	while (light_units.readFrom(input)) {
		frame_count++;

		// Scale intensities by tick period
		for (int j = 0; j < numPixels; j++) {
			light_units(j) /= static_cast<double>(tps);
		}

		// Loop through ticks (i) and pixels (j),
		//   accumulating light and emitting pixel fires
		for (int i = 0; i < tpf; i++, t++) {
			for (int j = 0; j < numPixels; j++) {
					PixelTracker pixel = pixels[j];
					pixel.accumulated_light += light_units(j);
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
}
