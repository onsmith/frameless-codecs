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
	** Plane index constants.
	*/
	const static int Y_PLANE = 0;
	const static int U_PLANE = 1;
	const static int V_PLANE = 2;

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
	uint8_t& intensityAt(int i) const;
	uint8_t& intensityAt(int plane, int i) const;
	uint8_t& intensityAt(int plane, int x, int y) const;

	/*
	** Overload copy assignment operator.
	*/
	Yuv420pFrame& operator=(Frame& const src) final;

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
};
