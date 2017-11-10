#include "PixelTracker.h"


PixelTracker::PixelTracker() :
	last_fire_time(0),
	accumulated_light(0.0) {
}

PixelTracker::PixelTracker(pixel_t i) :
	i(i),
	last_fire_time(0),
	accumulated_light(0.0) {
}

PixelTracker::PixelTracker(pixel_t i, decimation_t d) :
	i(i),
	d(d),
	last_fire_time(0),
	target_light(0x1 << d),
	accumulated_light(0.0) {
}

PixelTracker::light_t PixelTracker::lightDeficit() const {
	return target_light - accumulated_light;
}

bool PixelTracker::readyToFire() const {
	return accumulated_light >= target_light;
}

void PixelTracker::fire(time_t t) {
	accumulated_light -= target_light;
	last_fire_time = t;
}

void PixelTracker::updateDecimation(decimation_t d) {
	this->d = d;
	target_light = (0x1 << d);
}
