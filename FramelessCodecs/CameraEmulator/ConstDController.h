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
	decimation_t initD(index_t) final;

	/*
	** Gets a pixel's next d value given the prior (d, dt) for that pixel.
	*/
	decimation_t nextD(index_t, decimation_t, timedelta_t) final;

	/*
	** Constructor.
	*/
	ConstDController(decimation_t d);
};

