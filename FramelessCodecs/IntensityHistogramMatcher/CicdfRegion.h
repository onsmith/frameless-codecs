#pragma once

#include "Spline.h"


class CicdfRegion {
public:
	/*
	** Data types.
	*/
	typedef double intensity_t;
	typedef double percentage_t;


private:
	/*
	** Bounding box of this CicdfRegion within the larger Cicdf.
	*/
	const intensity_t  x0, x1; // x-axis bounds
	const percentage_t y0, y1; // y-axis bounds

	/*
	** Spline object representing the mathematical function within this region.
	*/
	Spline spline;


public:
	/*
	** Constructor.
	*/
	CicdfRegion(intensity_t, intensity_t, percentage_t, percentage_t);

	/*
	** Given a percentage which lies inside this region, calculates the
	**   corresponding intensity value.
	*/
	intensity_t intensityAt(percentage_t) const;

	/*
	** Given a intensity which lies inside this region, calculates the
	**   corresponding percentage value.
	*/
	percentage_t percentageAt(intensity_t) const;

	/*
	** Gets the lower and upper bounds of the region.
	*/
	intensity_t  intensityLowerBound() const;
	intensity_t  intensityUpperBound() const;
	percentage_t percentageLowerBound() const;
	percentage_t percentageUpperBound() const;
};
