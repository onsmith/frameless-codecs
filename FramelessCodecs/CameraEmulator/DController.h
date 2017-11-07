#pragma once

#include <cstdint>

#include "DataTypes.h"


class DController {
public:
	/*
	** Gets a pixel's initial d value.
	*/
	virtual decimation_t initD(index_t) = 0;

	/*
	** Gets a pixel's next d value given the prior (d, dt) for that pixel.
	*/
	virtual decimation_t nextD(index_t, decimation_t, timedelta_t) = 0;

	/*
	** Abstract classes should have a virtual destructor.
	*/
	virtual ~DController() = default;
};
