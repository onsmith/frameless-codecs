#pragma once

#include "Frame/GrayDoubleFrame.h"
#include "CameraEmulator/DataTypes.h"
#include "CameraEmulator/PixelFire.h"
#include "OrderedPixelFireStreamSource.h"
#include "GrayDoubleFrameStreamSink.h"

#include <vector>
using std::vector;


class FramelessStreamFramifier {
private:
	/*
	** Input source.
	*/
	OrderedPixelFireStreamSource input;

	/*
	** Output sink.
	*/
	GrayDoubleFrameStreamSink output;

	/*
	** Buffers frames of intensity data to send to the Sink object.
	*/
	GrayDoubleFrame frame;

	/*
	** Vector which stores the last time each pixel fired.
	*/
	vector<timestamp_t> lastFireTimes;

	/*
	** The current time, stored as a number of ticks since the video started.
	*/
	timestamp_t t;

	/*
	** Convenience methods to get the width, height, and number of pixels in the
	**   scene.
	*/
	int width() const;
	int height() const;
	size_t numPixels() const;

	/*
	** Given a pixel fire object, computes the corresponding intensity.
	*/
	inline double computeIntensity(const Intensity&);


public:
	/*
	** Ticks per second.
	*/
	static const long unsigned int tps = (0x1 << 14);

	/*
	** Frames per second.
	*/
	const long unsigned int fps;

	/*
	** Ticks per frame.
	*/
	const long unsigned int tpf;

	/*
	** Constructor.
	*/
	FramelessStreamFramifier(
		istream& input,
		ostream& output,
		int width,
		int height,
		int fps
	);

	/*
	** Pulls PixelFire objects from the Source, framifies them, and emits a
	**   single Frame to the Sink.
	*/
	void framifyPixelFires();
};
