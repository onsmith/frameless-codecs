#pragma once


class Spline {
public:
	/*
	** Internal data type.
	*/
	typedef double number_t;


private:
	/*
	** Spline coefficients.
	*/
	const number_t a3, a2, a1, a0;

public:
	/*
	** Constructors.
	*/
	Spline(number_t, number_t, number_t, number_t);
	Spline(number_t, number_t, number_t, number_t, number_t, number_t);

	/*
	** Evaluates the spline at a given point.
	*/
	number_t operator()(number_t) const;
};
