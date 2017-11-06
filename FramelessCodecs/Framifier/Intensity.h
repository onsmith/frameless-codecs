#pragma once

#include "CameraEmulator/DataTypes.h"


struct Intensity {
public:
	decimation_t d;
	uint16_t     dt;

	Intensity() = default;
	Intensity(decimation_t, uint16_t);
};
