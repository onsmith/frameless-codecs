#pragma once

#include "DataTypes.h"


struct PixelFire {
public:
	index_t i;
	decimation_t d;
	timedelta_t dt;

	PixelFire() = default;
	PixelFire(index_t, decimation_t, timedelta_t);
};
