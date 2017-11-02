#pragma once

#include "DController.h"


class TargetDController final : public DController {
private:
	/*
	** Minimum and maximum d values.
	*/
	static const int MIN_D = 0x0;
	static const int MAX_D = 0xF;

	/*
	** Stores the target dt value.
	*/
	const timedelta_t target_dt;

	/*
	** Stores the initial d value.
	*/
	const decimation_t init_d;


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
	TargetDController(decimation_t init_d, timedelta_t target_dt);
};

