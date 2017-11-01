#pragma once

#include <cstdint>


class DController {
public:
	/*
	** Data type for a D value.
	*/
	typedef uint8_t decimation_t;

	/*
	** Data type for a dt value.
	*/
	typedef uint8_t timedelta_t;

	/*
	** Initializes a pixel's D value.
	*/
	virtual decimation_t init(int x, int y) = 0;

	/*
	** Changes a pixel's D value given the prior D value.
	*/
	virtual decimation_t next(int x, int y, timedelta_t last_dt) = 0;

	/*
	** Abstract classes should have a virtual destructor.
	*/
	virtual ~DController() = default;
};
