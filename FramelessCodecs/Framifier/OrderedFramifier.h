#pragma once

#include <cstdint>

#include <vector>
using std::vector;

#include <iostream>
using std::istream;
using std::ostream;

#include "Frame/GrayDoubleFrame.h"
#include "CameraEmulator/PixelFire.h"


#define TICKS_PER_SECOND 1000


class OrderedFramifier {
public:
	/*
	** Data types.
	*/
	typedef uint64_t time_t;


private:
	/*
	** Ticks per second.
	*/
	time_t tps = TICKS_PER_SECOND;

	/*
	** Ticks per frame.
	*/
	time_t tpf;

	/*
	** Frames per second.
	*/
	time_t fps;

	/*
	** Input stream.
	*/
	istream& input;

	/*
	** Output stream.
	*/
	ostream& output;

	/*
	** Buffers the next PixelFire object from the input stream.
	*/
	PixelFire pixel;

	/*
	** Buffers frames of intensity data to write to the output stream.
	*/
	GrayDoubleFrame frame;

	/*
	** Stores the next time each pixel will change.
	*/
	vector<time_t> nextChangeTime;

	/*
	** The current frame number.
	*/
	unsigned long int frameNumber = 0;


public:
	/*
	** Constructor.
	*/
	OrderedFramifier(
		istream& input,
		ostream& output,
		size_t width,
		size_t height,
		int fps
	);

	/*
	** Convenience method to get the width of the frame.
	*/
	inline size_t width() const;

	/*
	** Convenience methods to get the height of the frame.
	*/
	inline size_t height() const;

	/*
	** Convenience methods to get the number of pixels in the scene.
	*/
	inline size_t numPixels() const;

	/*
	** Pulls PixelFire objects from the input stream as necessary, framifies
	**   them, and emits a single GrayDoubleFrame to the output stream.
	*/
	void framifyPixelFires();
};
