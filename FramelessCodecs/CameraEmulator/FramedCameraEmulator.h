#pragma once

#include <fstream>
using std::istream;

#include "DataTypes.h"
#include "PixelFire.h"
#include "PixelTracker.h"
#include "ConstDController.h"
#include "GrayDoubleFrameStreamSource.h"
#include "PixelFireConsoleSink.h"


class FramedCameraEmulator {
private:
	/*
	** Ticks per second.
	*/
	static const long unsigned int tps = 4000;

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
	GrayDoubleFrameStreamSource input;

	/*
	** Output sink.
	*/
	PixelFireConsoleSink output;

	/*
	** Decimation controller.
	*/
	ConstDController dControl;

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
	void initializePixelTrackers();

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
		istream& input,
		int width,
		int height,
		int fps
	);

	/*
	** Pulls a frame from the Source, emulates it, and emits PixelFire objects.
	*/
	void emulateFrame();
};
