#pragma once

#include "DataFrame.h"

#include <cstdint>


class Gray16leFrame : public DataFrame<uint16_t> {
public:
	/*
	** Constructor.
	*/
	Gray16leFrame(int width, int height);

	/*
	** Changes the dimensions of the frame.
	*/
	void resize(int width, int height);

	/*
	** Exposes access to individual intensities in the frame.
	*/
	uint16_t& intensityAt(int i);
	uint16_t& intensityAt(int x, int y);

	/*
	** Overload copy assignment operator.
	*/
	Gray16leFrame& operator=(Frame& src) final;

	/*
	** Methods to get an intensity value by specifying its location in the frame.
	*/
	uint8_t  getIntensityAsByte  (int plane, int x, int y) final;
	uint16_t getIntensityAs16Bits(int plane, int x, int y) final;
	double   getIntensityAsDouble(int plane, int x, int y) final;
};
