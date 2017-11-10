#pragma once

#include "DController.h"
#include "TargetDController.h"


class RoiDController final : public DController {
private:
	/*
	** Encapsulates two TargetDControllers.
	*/
	TargetDController roi;
	TargetDController bg;

	/*
	** Region of interest.
	*/
	const index_t x_min;
	const index_t y_min;
	const index_t x_max;
	const index_t y_max;

	/*
	** Stride of the scene.
	*/
	const int stride;

	/*
	** Determines whether a given pixel index is located in the region of
	**   interest.
	*/
	bool isInRoi(index_t) const;

	/*
	** Calculate the coordinates for a given pixel index.
	*/
	index_t x(index_t) const;
	index_t y(index_t) const;


public:
	/*
	** Constructor.
	*/
	RoiDController(
		decimation_t roi_init_d,
		timedelta_t  roi_target_dt,
		decimation_t bg_init_d,
		timedelta_t  bg_target_dt,
		index_t stride,
		index_t x_min,
		index_t y_min,
		index_t x_max,
		index_t y_max
	);

	/*
	** Gets a pixel's initial d value.
	*/
	decimation_t initD(index_t) final;

	/*
	** Gets a pixel's next d value given the prior (d, dt) for that pixel.
	*/
	decimation_t nextD(index_t, decimation_t, timedelta_t) final;
};
