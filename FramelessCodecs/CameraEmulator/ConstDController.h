#pragma once

#include "DController.h"


class ConstDController final : public DController {
private:
	/*
	** Stores the unchanging d value.
	*/
	const decimation_t d;

	/*
	** Initialize a pixel's D value.
	*/
	decimation_t init(int x, int y);

	/*
	** Changes a pixel's D value given the prior D value.
	*/
	decimation_t next(int x, int y, timedelta_t last_dt);

public:
	ConstDController(decimation_t d);
};

