#pragma once

#include "IntensityBuffer.h"

#include "Frame/GrayDoubleFrame.h"

#include "CameraEmulator/DataTypes.h"
#include "CameraEmulator/PixelFire.h"

#include <vector>
using std::vector;

#include <iostream>
using std::ostream;


#define TICKS_PER_SECOND 1000


class UnorderedFramifier {
private:
	/*
	** Ticks per second.
	*/
	static const long unsigned int tps = TICKS_PER_SECOND;

	/*
	** Ticks per frame.
	*/
	const long unsigned int tpf;

	/*
	** Frames per second.
	*/
	const long unsigned int fps;

	/*
	** Input stream is maanged by an IntensityBuffer.
	*/
	IntensityBuffer input;

	/*
	** Output stream.
	*/
	ostream& output;

	/*
	** Buffers frames of intensity data to write to the output stream.
	*/
	GrayDoubleFrame frame;

	/*
	** Stores the next time each pixel will fire.
	*/
	vector<timestamp_t> nextFireTime;

	/*
	** The current frame number.
	*/
	unsigned long int frameNumber = 0;

	/*
	** Given a pixel fire object, computes the corresponding intensity.
	*/
	inline double computeIntensity(const Intensity&) const;

	/*
	** Calculates the next fire time for each pixel and initializes the buffer.
	*/
	inline void initializeBuffer();


public:
	/*
	** Constructor.
	*/
	UnorderedFramifier(
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
