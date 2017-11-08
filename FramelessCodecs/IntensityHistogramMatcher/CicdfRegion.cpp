#include "CicdfRegion.h"

#include <cmath>


#define ZERO_TOLERANCE            0.000001F
#define MAX_ITERATIONS            1000000
#define DERIVATIVE_AT_LOWER_POINT 0.0
#define DERIVATIVE_AT_UPPER_POINT 0.0


CicdfRegion::CicdfRegion(
	intensity_t  intensity_min,
	intensity_t  intensity_max,
	percentage_t percentage_min,
	percentage_t percentage_max
) :
	x0(intensity_min),
	x1(intensity_max),
	y0(percentage_min),
	y1(percentage_max),
	spline(intensity_min, percentage_min, intensity_max, percentage_max, DERIVATIVE_AT_LOWER_POINT, DERIVATIVE_AT_UPPER_POINT) {
}

CicdfRegion::percentage_t CicdfRegion::percentageAt(intensity_t intensity) const {
	return spline(intensity);
}

CicdfRegion::intensity_t CicdfRegion::intensityAt(percentage_t percentage) const {
	intensity_t x_min = x0;
	intensity_t x_max = x1;
	for (int i = 0; i < MAX_ITERATIONS; i++) {
		intensity_t  x_mid = (x_max + x_min) / 2;
		percentage_t y_mid = spline(x_mid) - percentage;
		if (y_mid < -ZERO_TOLERANCE) {
			x_min = x_mid;
		} else if (y_mid < ZERO_TOLERANCE) {
			break;
		} else {
			x_max = x_mid;
		}
	}
	return (x_max + x_min) / 2;
}

CicdfRegion::intensity_t CicdfRegion::intensityLowerBound() const {
	return x0;
}

CicdfRegion::intensity_t CicdfRegion::intensityUpperBound() const {
	return x1;
}

CicdfRegion::percentage_t CicdfRegion::percentageLowerBound() const {
	return y0;
}

CicdfRegion::percentage_t CicdfRegion::percentageUpperBound() const {
	return y1;
}
