#pragma once

#include "DataTypes.h"


struct PixelTracker {
public:
	/*
	** The pixel's coordinates in the 2D frame.
	*/
	coordinate_t x, y;

	/*
	** The pixel's current decimation value.
	*/
	decimation_t d;

	/*
	** The timestamp when the pixel was last fired.
	*/
	timestamp_t last_fire_time;

	/*
	** The amount of light accumulated by the pixel.
	*/
	light_t accumulated_light;

	/*
	** The amount of light that must be accumulated before the pixel fires.
	*/
	light_t target_light;
};
