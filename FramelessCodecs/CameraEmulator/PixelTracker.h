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
	** The amount of light accumulated by the pixel.
	*/
	light_t accumulated_light;

	/*
	** The amount of light that must be accumulated before the pixel fires.
	*/
	light_t target_light;

	/*
	** The timestamp when the pixel was last fired.
	*/
	timestamp_t last_fire_time;

	/*
	** The time at which the pixel next fires (for use with priority queue).
	*/
	timestamp_t next_fire_time;
};
