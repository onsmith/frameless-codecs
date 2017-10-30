#pragma once

#include "DataFrame.h"

#include <cstdint>


/**
 * Yuv444pFrame is a concrete implementation of the DataFrame<T> class, and
 *   therefore defines the frame's intensity addressing scheme. A Yuv444pFrame
 *   object represents a yuv color format, 8 bit color component depth,
 *   planar-organized video frame with no chroma subsampling.
 */
class Yuv444pFrame final : public DataFrame<uint8_t> {
private:
	/*
	** Stores the number of pixels in each plane.
	*/
	int numPixels_;


public:
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
	** Overload copy assignment operator.
	*/
	Yuv444pFrame& operator=(Frame& const src) final;

	/*
	** Methods to get an intensity value by specifying its location in the frame.
	*/
	uint8_t  getIntensityAsByte  (int plane, int i       ) const final;
	uint8_t  getIntensityAsByte  (int plane, int x, int y) const final;
	uint16_t getIntensityAs16Bits(int plane, int i       ) const final;
	uint16_t getIntensityAs16Bits(int plane, int x, int y) const final;
	double   getIntensityAsDouble(int plane, int i       ) const final;
	double   getIntensityAsDouble(int plane, int x, int y) const final;
};
