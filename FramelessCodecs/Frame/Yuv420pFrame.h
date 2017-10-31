#pragma once

#include "DataFrame.h"
#include "Yuv422pFrame.h"
#include "Yuv420pFrame.h"
#include "GrayDoubleFrame.h"
#include "Gray16leFrame.h"

#include <cstdint>


class Yuv420pFrame final : public DataFrame<uint8_t> {
private:
	/*
	** Stores the stride of each plane.
	*/
	int strides_[3];

	/*
	** Stores the memory offsets of each plane.
	*/
	int offsets_[3];


public:
	/*
	** Constructor.
	*/
	Yuv420pFrame(int width, int height);

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
	Yuv420pFrame& operator=(Frame& src) final;

	/*
	** Methods to get an intensity value by specifying its location in the frame.
	*/
	uint8_t  getIntensityAsByte  (int plane, int x, int y) final;
	uint16_t getIntensityAs16Bits(int plane, int x, int y) final;
	double   getIntensityAsDouble(int plane, int x, int y) final;
};
