#pragma once

#include <cstdint>

#include <vector>
using std::vector;

#include <fstream>
using std::istream;
using std::ostream;

#include "PixelFire.h"
#include "PixelTracker.h"
#include "VideoLightSource.h"
#include "ConstDController.h"
#include "TargetDController.h"
#include "RoiDController.h"


class UnorderedCameraEmulator {
public:
	/*
	** Data types.
	*/
	typedef uint64_t time_t;
	typedef uint64_t pixel_t;
	typedef double   light_t;


private:
	/*
	** Maximum allowed dt (in ticks) before pixels are prematurely fired.
	*/
	const long unsigned int DT_MAX = 0xFF;

	/*
	** LightSource object providing the scene light intensity information.
	*/
	VideoLightSource source;

	/*
	** Output stream (for writing pixel fire information).
	*/
	ostream& output;

	/*
	** Decimation controller.
	*/
	RoiDController dControl;
	//TargetDController dControl;
	//ConstDController dControl;

	/*
	** Vector of PixelTracker objects, which track information for each pixel.
	*/
	vector<PixelTracker> pixels;

	/*
	** Current frame number.
	*/
	time_t currentFrame = 0;

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
	** Fires a given pixel at a given time, creating a single new PixelFire
	**   object and writing it to the output stream.
	*/
	inline void firePixel(PixelTracker&, time_t);
	
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
		pixel_t width,
		pixel_t height,
		time_t fps
	);

	/*
	** Emulates the next frame of light scene information, emitting PixelFire
	**   objects to the output stream as necessary.
	*/
	void emulateFrame();
};
