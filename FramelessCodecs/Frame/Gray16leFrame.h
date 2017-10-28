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
	uint16_t& intensityAt(int i)               const final;
	uint16_t& intensityAt(int x, int y)        const final;
	uint16_t& intensityAt(int _, int x, int y) const final;
};
