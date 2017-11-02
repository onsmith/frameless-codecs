#pragma once

#include "DataTypes.h"


struct PixelFire {
public:
	coordinate_t x, y;
	decimation_t d;
	timedelta_t  dt;

	PixelFire() = default;
	PixelFire(coordinate_t x, coordinate_t y, coordinate_t d, coordinate_t dt);
};
