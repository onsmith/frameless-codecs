#pragma once

#include "DataFrame.h"


class GrayDoubleFrame : public DataFrame<double> {
public:
	/*
	** Constructor.
	*/
	GrayDoubleFrame(int width, int height);

	/*
	** Changes the dimensions of the frame.
	*/
	void resize(int width, int height);

	/*
	** Exposes access to individual intensities in the frame.
	*/
	double& intensityAt(int i) const;
	double& intensityAt(int x, int y) const;
	double& intensityAt(int _, int x, int y) const;

	/*
	** Overload copy assignment operator.
	*/
	GrayDoubleFrame& operator=(Frame& const src) final;

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
