#pragma once

#include <cstdint>

#include "DataTypes.h"


class DController {
public:
	/*
	** Gets a pixel's initial d value.
	*/
	virtual decimation_t initD(int x, int y) = 0;

	/*
	** Gets a pixel's next d value given the prior (d, dt) for that pixel.
	*/
	virtual decimation_t nextD(int x, int y, decimation_t last_d, timedelta_t last_dt) = 0;

	/*
	** Abstract classes should have a virtual destructor.
	*/
	virtual ~DController() = default;
};
