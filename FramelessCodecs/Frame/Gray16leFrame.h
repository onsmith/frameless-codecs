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
	uint16_t& intensityAt(int i) const;
	uint16_t& intensityAt(int x, int y) const;
	uint16_t& intensityAt(int _, int x, int y) const;

	/*
	** Overload copy assignment operator.
	*/
	Gray16leFrame& operator=(Frame& const src) final;

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
