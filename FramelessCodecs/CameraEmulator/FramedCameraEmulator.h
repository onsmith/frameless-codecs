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
	** Ticks per second.
	*/
	const long unsigned int tps;

	/*
	** Frames per second.
	*/
	const long int fps;

	/*
	** Ticks per frame.
	*/
	const long int tpf;

	/*
	** Input source.
	*/
	Source<GrayDoubleFrame>& input;

	/*
	** Output sink.
	*/
	Sink<PixelFire>& output;

	/*
	** Decimation controller.
	*/
	DController &dController;

	/*
	** Vector of PixelTracker objects, storing pixel information.
	*/
	vector<PixelTracker> pixels;

	/*
	** The current time, stored as a number of ticks since the video started.
	*/
	timestamp_t t;

	/*
	** Buffers frames of intensity data from the Source object.
	*/
	GrayDoubleFrame frame;

	/*
	** Initializes all internal PixelTracker objects.
	*/
	void initPixelTrackers();

	/*
	** Convenience methods to get the width, height, and number of pixels in the
	**   scene.
	*/
	int width() const;
	int height() const;
	int numPixels() const;


public:
	/*
	** Constructor.
	*/
	FramedCameraEmulator(
		int width,
		int height,
		int ticks_per_second,
		int frames_per_second,
		Source<GrayDoubleFrame>& input,
		Sink<PixelFire>& output,
		DController& dController
	);

	/*
	** Pulls a frame from the Source, emulates it, and emits PixelFire objects.
	*/
	void emulateFrame();
};
