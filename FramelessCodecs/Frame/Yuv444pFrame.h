#pragma once

#include "DataFrame.h"
#include "Yuv422pFrame.h"
#include "Yuv420pFrame.h"
#include "GrayDoubleFrame.h"
#include "Gray16leFrame.h"

#include <cstdint>


/**
 * Yuv444pFrame is a concrete implementation of the DataFrame<T> class, and
 *   therefore defines the frame's intensity addressing scheme. A Yuv444pFrame
 *   object represents a yuv color format, 8 bit color component depth,
 *   planar-organized video frame with no chroma subsampling.
 */
class Yuv444pFrame : public DataFrame<uint8_t> {
private:
	/*
	** Stores the number of pixels in each plane.
	*/
	int numPixels_;


public:
	/*
	** Plane index constants.
	*/
	const static int Y_PLANE = 0;
	const static int U_PLANE = 1;
	const static int V_PLANE = 2;

	/*
	** Constructor.
	*/
	Yuv444pFrame(int width, int height);

	/*
	** Changes the dimensions of the frame.
	*/
	void resize(int width, int height);

	/*
	** Exposes access to individual intensities in the frame.
	*/
	uint8_t& intensityAt(int i) const;
	uint8_t& intensityAt(int plane, int i) const;
	uint8_t& intensityAt(int plane, int x, int y) const;

	/*
	** Overload the assignment operator for frame transcoding.
	*/
	Yuv444pFrame& operator=(Yuv422pFrame& const);
	Yuv444pFrame& operator=(Yuv420pFrame& const);
	Yuv444pFrame& operator=(GrayDoubleFrame& const);
	Yuv444pFrame& operator=(Gray16leFrame& const);
};
