#include "CicdfRegion.h"

#include <cmath>


#define ZERO_TOLERANCE            0.000001F
#define DERIVATIVE_AT_LOWER_POINT 0.0
#define DERIVATIVE_AT_UPPER_POINT 0.0


/*
** Evaluates a cubic function with given coefficients at a given point.
*/
static inline double evaluate_cubic(const double a3, const double a2, const double a1, const double a0, const double x) {
	return a3*x*x*x + a2*x*x + a1*x + a0;
}


/*
** Uses a binary search algorithm to find the zero of a given cubic function.
**   The cubic specified must (1) have a zero in the range specified and must
**   (2) be monotonically increasing in the range specified.
*/
static double find_cubic_zero(const double a3, const double a2, const double a1, const double a0, const double x_min, const double x_max) {
	const double x_mid = (x_min + x_max) / 2;
	const double y_mid = evaluate_cubic(a3, a2, a1, a0, x_mid);
	if (y_mid < -ZERO_TOLERANCE) {
		return find_cubic_zero(a3, a2, a1, a0, x_mid, x_max);
	} else if (y_mid < ZERO_TOLERANCE) {
		return x_mid;
	} else {
		return find_cubic_zero(a3, a2, a1, a0, x_min, x_mid);
	}
}


/*
** These functions calculate the four coefficients of a cubic function passing
**   through the points p0 = (x0, y0) and p1 = (x1, y1) with derivative d0 at
**   point p0 and derivative d1 at point p1.
*/
static inline double a3(const double x0, const double y0, const double x1, const double y1, const double d0, const double d1) {
	return (d0*(x0 - x1) + d1*(x0 - x1) - 2*(y0 - y1)) / pow(x0 - x1, 3);
}

static inline double a2(const double x0, const double y0, const double x1, const double y1, const double d0, const double d1) {
	return (-d0*(x0*x0 + x0*x1 - 2*x1*x1) + d1*(-2*x0*x0 + x0*x1 + x1*x1) + 3*(x0 + x1)*(y0 - y1)) / pow(x0 - x1, 3);
}

static inline double a1(const double x0, const double y0, const double x1, const double y1, const double d0, const double d1) {
	return (d1*x0*(x0*x0 + x0*x1 - 2*x1* x1) - x1*(d0*(-2*x0* x0 + x0*x1 + x1*x1) + 6*x0*(y0 - y1))) / pow(x0 - x1, 3);
}

static inline double a0(const double x0, const double y0, const double x1, const double y1, const double d0, const double d1) {
	return ((d1*x0*x0*x1 + d0*x0*x1*x1)*(x1 - x0) + 3*x0*x1*x1*y0 - x1*x1*x1*y0 + x0*x0*x0*y1 - 3*x0*x0*x1*y1) / pow(x0 - x1, 3);
}


CicdfRegion::CicdfRegion(
	intensity_t  intensity_min,
	intensity_t  intensity_max,
	percentage_t percentage_min,
	percentage_t percentage_max
) :
	intensityMin(intensity_min),
	intensityMax(intensity_max),
	percentageMin(percentage_min),
	percentageMax(percentage_max) {
}

CicdfRegion::intensity_t CicdfRegion::intensityAt(percentage_t percentage) const {
	const double b3 = a3(intensityMin, percentageMin, intensityMax, percentageMax, DERIVATIVE_AT_LOWER_POINT, DERIVATIVE_AT_UPPER_POINT);
	const double b2 = a2(intensityMin, percentageMin, intensityMax, percentageMax, DERIVATIVE_AT_LOWER_POINT, DERIVATIVE_AT_UPPER_POINT);
	const double b1 = a1(intensityMin, percentageMin, intensityMax, percentageMax, DERIVATIVE_AT_LOWER_POINT, DERIVATIVE_AT_UPPER_POINT);
	const double b0 = a0(intensityMin, percentageMin, intensityMax, percentageMax, DERIVATIVE_AT_LOWER_POINT, DERIVATIVE_AT_UPPER_POINT);
	return find_cubic_zero(b3, b2, b1, b0 - percentage, intensityMin, intensityMax);
}

CicdfRegion::percentage_t CicdfRegion::percentageAt(intensity_t intensity) const {
	const double b3 = a3(intensityMin, percentageMin, intensityMax, percentageMax, DERIVATIVE_AT_LOWER_POINT, DERIVATIVE_AT_UPPER_POINT);
	const double b2 = a2(intensityMin, percentageMin, intensityMax, percentageMax, DERIVATIVE_AT_LOWER_POINT, DERIVATIVE_AT_UPPER_POINT);
	const double b1 = a1(intensityMin, percentageMin, intensityMax, percentageMax, DERIVATIVE_AT_LOWER_POINT, DERIVATIVE_AT_UPPER_POINT);
	const double b0 = a0(intensityMin, percentageMin, intensityMax, percentageMax, DERIVATIVE_AT_LOWER_POINT, DERIVATIVE_AT_UPPER_POINT);
	return evaluate_cubic(b3, b2, b1, b0, intensity);
}
