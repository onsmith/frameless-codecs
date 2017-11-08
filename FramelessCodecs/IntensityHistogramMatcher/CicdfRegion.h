#pragma once


class CicdfRegion {
public:
	/*
	** Data types.
	*/
	typedef double percentage_t;
	typedef double intensity_t;

	/*
	** Bounding box of this CicdfRegion within the larger Cicdf.
	*/
	const intensity_t  intensityMin,  intensityMax;  // x-axis bounds
	const percentage_t percentageMin, percentageMax; // y-axis bounds

	/*
	** Constructors.
	*/
	CicdfRegion() = default;
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
};
