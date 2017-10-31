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
	double& intensityAt(int i);
	double& intensityAt(int x, int y);
	double& intensityAt(int _, int x, int y);

	/*
	** Overload copy assignment operator.
	*/
	GrayDoubleFrame& operator=(Frame& src) final;

	/*
	** Methods to get an intensity value by specifying its location in the frame.
	*/
	uint8_t  getIntensityAsByte  (int plane, int i       ) final;
	uint8_t  getIntensityAsByte  (int plane, int x, int y) final;
	uint16_t getIntensityAs16Bits(int plane, int i       ) final;
	uint16_t getIntensityAs16Bits(int plane, int x, int y) final;
	double   getIntensityAsDouble(int plane, int i       )  final;
	double   getIntensityAsDouble(int plane, int x, int y) final;
};
