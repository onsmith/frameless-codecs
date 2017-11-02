#pragma once

#include "DController.h"


class ConstDController final : public DController {
private:
	/*
	** Stores the unchanging d value.
	*/
	const decimation_t d;


public:
	/*
	** Gets a pixel's initial d value.
	*/
	decimation_t initD(int x, int y) final;

	/*
	** Gets a pixel's next d value given the prior (d, dt) for that pixel.
	*/
	decimation_t nextD(int x, int y, decimation_t last_d, timedelta_t last_dt) final;

	/*
	** Constructor.
	*/
	ConstDController(decimation_t d);
};

