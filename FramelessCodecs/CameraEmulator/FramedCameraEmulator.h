#pragma once

#include <fstream>
using std::istream;
using std::ostream;

#include "DataTypes.h"
#include "Source.h"
#include "Sink.h"
#include "PixelFire.h"
#include "PixelTracker.h"
#include "DController.h"


class FramedCameraEmulator {
private:
	/*
	** Frame width.
	*/
	const int width;

	/*
	** Frame height.
	*/
	const int height;

	/*
	** Frames per second.
	*/
	const long int fps;

	/*
	** Ticks per second.
	*/
	const long unsigned int tps;

	/*
	** Ticks per frame.
	*/
	const long int tpf;

	/*
	** Decimation controller.
	*/
	DController &dController;

	/*
	** Vector of PixelTracker objects, storing pixel information.
	*/
	vector<PixelTracker> pixels;


public:
	/*
	** Constructor.
	*/
	FramedCameraEmulator(
		int width,
		int height,
		int ticks_per_second,
		int frames_per_second,
		Source<GrayDoubleFrame> input,
		Sink<PixelFire> output,
		DController& dController
	);

	/*
	** Main method that runs the emulator; returns number of frames read.
	*/
	int emulate(istream& input, ostream& output) const;
};
