#pragma once

#include <vector>
using std::vector;

#include <fstream>
using std::istream;
using std::ostream;

#include "DataTypes.h"
#include "PixelFire.h"
#include "PixelTracker.h"
#include "ConstDController.h"
#include "TargetDController.h"

#include "Frame/GrayDoubleFrame.h"


#define CONSTANT_D 8
//#define INITIAL_D  8
//#define TARGET_DT  8


class UnorderedCameraEmulator {
private:
	/*
	** Ticks per second.
	*/
	static const long unsigned int tps = (0x1 << 14);

	/*
	** Frames per second.
	*/
	const long int fps;

	/*
	** Ticks per frame.
	*/
	const long int tpf;

	/*
	** Input stream.
	*/
	istream& input;

	/*
	** Output stream.
	*/
	ostream& output;

	/*
	** Decimation controller.
	*/
	ConstDController dControl = ConstDController(CONSTANT_D);
	//TargetDController dControl = TargetDController(INITIAL_D, TARGET_DT);

	/*
	** Vector of PixelTracker objects, which track information for each pixel.
	*/
	vector<PixelTracker> pixels;

	/*
	** The current frame number.
	*/
	unsigned long int frameNumber = 0;

	/*
	** Buffers frames of intensity data from the input stream.
	*/
	GrayDoubleFrame frame;

	/*
	** Internal method to initialize a PixelTracker object for every pixel.
	*/
	inline void initializePixelTrackers();

	/*
	** Writes a PixelFire to the output stream using a binary representation.
	*/
	inline void writeBinary(const PixelFire&);

	/*
	** Writes a PixelFire to the output stream using a human-readable text
	**   representation (for use with cout).
	*/
	inline void writeText(const PixelFire&);

	/*
	** Fires a given pixel at a given time, creating a new PixelFire object and
	**   writing it to the output stream.
	*/
	inline void firePixel(PixelTracker&, timestamp_t);

	/*
	** Scales a raw intensity value read from the input stream.
	*/
	inline double scaleIntensity(double) const;

	/*
	** Given a PixelTracker and the amount of light to accumulate during a single
	**   tick, calculates and returns the number of ticks that will pass before
	**   the pixel emits a PixelFire object.
	*/
	inline timedelta_t timestepsUntilNextFire(const PixelTracker&, light_t) const;
	
	/*
	** Convenience method to retrieve the width of the frame.
	*/
	inline int width() const;
	
	/*
	** Convenience method to retrieve the height of the frame.
	**   scene.
	*/
	inline int height() const;
	
	/*
	** Convenience method to retrieve the number of pixels in the scene.
	*/
	inline size_t numPixels() const;


public:
	/*
	** Constructor.
	*/
	UnorderedCameraEmulator(
		istream& input,
		ostream& output,
		int width,
		int height,
		int fps
	);

	/*
	** Pulls a frame from the Source, emulates it, and emits PixelFire objects.
	*/
	void emulateFrame();
};
