#pragma once

#include "CicdfRegion.h"

#include <vector>
using std::vector;


class Cicdf {
public:
	/*
	** Data types.
	*/
	typedef CicdfRegion::percentage_t percentage_t;
	typedef CicdfRegion::intensity_t  intensity_t;


private:
	/*
	** Manages an internal list of CicdfRegion objects.
	*/
	vector<CicdfRegion> regions;

	/*
	** Stores the overall intensity bounds.
	*/
	const intensity_t intensity_min;
	const intensity_t intensity_max;

	/*
	** Sequentially adds a new region of interest to the Cicdf.
	*/
	void addRegion(intensity_t, percentage_t);


public:
	/*
	** Constructors.
	*/
	Cicdf();
	Cicdf(intensity_t, intensity_t);

	/*
	** Adds a new region of interest to the Cicdf.
	*/
	void addRegion(intensity_t, percentage_t, intensity_t, percentage_t);

	/*
	** Given a percentage, calculates the corresponding intensity value.
	*/
	intensity_t intensityAt(percentage_t) const;

	/*
	** Given a intensity, calculates the corresponding percentage value.
	*/
	percentage_t percentageAt(intensity_t) const;
};
