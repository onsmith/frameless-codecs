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
	double& intensityAt(int i)               const final;
	double& intensityAt(int x, int y)        const final;
	double& intensityAt(int _, int x, int y) const final;
};
