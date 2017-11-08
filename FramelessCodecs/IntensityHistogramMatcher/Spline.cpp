#include "Spline.h"

#include <cmath>


Spline::Spline(number_t a3, number_t a2, number_t a1, number_t a0) :
	a3(a3),
	a2(a2),
	a1(a1),
	a0(a0) {
}

Spline::Spline(number_t x0, number_t y0, number_t x1, number_t y1, number_t d0, number_t d1) :
	a3((d0*(x0 - x1) + d1*(x0 - x1) - 2*(y0 - y1)) / pow(x0 - x1, 3)),
	a2((-d0*(x0*x0 + x0*x1 - 2*x1*x1) + d1*(-2*x0*x0 + x0*x1 + x1*x1) + 3*(x0 + x1)*(y0 - y1)) / pow(x0 - x1, 3)),
	a1((d1*x0*(x0*x0 + x0*x1 - 2*x1* x1) - x1*(d0*(-2*x0* x0 + x0*x1 + x1*x1) + 6*x0*(y0 - y1))) / pow(x0 - x1, 3)),
	a0(((d1*x0*x0*x1 + d0*x0*x1*x1)*(x1 - x0) + 3*x0*x1*x1*y0 - x1*x1*x1*y0 + x0*x0*x0*y1 - 3*x0*x0*x1*y1) / pow(x0 - x1, 3)) {
}

Spline::number_t Spline::operator()(number_t x) const {
	return a0 + x*(a1 + x*(a2 + x*a3));
}
