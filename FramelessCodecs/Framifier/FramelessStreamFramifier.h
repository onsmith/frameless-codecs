#pragma once

#include "Frame/GrayDoubleFrame.h"
#include "CameraEmulator/DataTypes.h"
#include "CameraEmulator/PixelFire.h"
#include "PixelFireStreamSource.h"
#include "GrayDoubleFrameStreamSink.h"

#include <vector>
using std::vector;


class FramelessStreamFramifier {
private:
	/*
	** Input source.
	*/
	PixelFireStreamSource input;

	/*
	** Output sink.
	*/
	GrayDoubleFrameStreamSink output;

	/*
	** Buffers the next PixelFire object from the Source.
	*/
	PixelFire pixel;

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
	long int t;

	/*
	** Convenience methods to get the width, height, and number of pixels in the
	**   scene.
	*/
	int width() const;
	int height() const;
	size_t numPixels() const;

	/*
	** Convenience method to get a pixel's index given its x and y coordinates.
	*/
	inline size_t index(const PixelFire&) const;

	/*
	** Given a pixel fire object, computes the corresponding intensity.
	*/
	inline double computeIntensity(const PixelFire&);


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
