#pragma once

#include "DataFrame.h"

#include <cstdint>


/**
 * Yuv444pFrame is a concrete implementation of the DataFrame<T> class, and
 *   therefore defines the frame's intensity addressing scheme. A Yuv422pFrame
 *   object represents a yuv color format, 8 bit color component depth,
 *   planar-organized video frame with 4:2:2 chroma subsampling.
 */
class Yuv422pFrame final : public DataFrame<uint8_t> {
private:
	/*
	** Stores the stride of each plane.
	*/
	int strides_[3];

	/*
	** Stores the memory offset of each plane.
	*/
	int offsets_[3];


public:
	/*
	** Constructor.
	*/
	Yuv422pFrame(int width, int height);

	/*
	** Changes the dimensions of the frame.
	*/
	void resize(int width, int height) final;

	/*
	** Exposes access to individual intensities in the frame.
	*/
	uint8_t& intensityAt(int i);
	uint8_t& intensityAt(int plane, int i);
	uint8_t& intensityAt(int plane, int x, int y);

	/*
	** Overload copy assignment operator.
	*/
	Yuv422pFrame& operator=(Frame& src) final;

	/*
	** Methods to get an intensity value by specifying its location in the frame.
	*/
	uint8_t  getIntensityAsByte  (int plane, int i       ) final;
	uint8_t  getIntensityAsByte  (int plane, int x, int y) final;
	uint16_t getIntensityAs16Bits(int plane, int i       ) final;
	uint16_t getIntensityAs16Bits(int plane, int x, int y) final;
	double   getIntensityAsDouble(int plane, int i       ) final;
	double   getIntensityAsDouble(int plane, int x, int y) final;
};
