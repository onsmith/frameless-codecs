#include "FramelessIntensity.h"

FramelessIntensity::FramelessIntensity(decimation_t d, uint16_t dt) :
	d(d),
	dt(dt) {
}

double FramelessIntensity::toDouble(uint64_t ticks_per_second) const {
	return toDouble(d, dt, ticks_per_second);
}

double FramelessIntensity::toDouble(decimation_t d, time_t dt, uint64_t ticks_per_second) {
	double intensity = (static_cast<double>(0x1 << d) / dt) * ticks_per_second;
	//intensity -= 1;
	intensity /= 50000;
	return intensity;
}
