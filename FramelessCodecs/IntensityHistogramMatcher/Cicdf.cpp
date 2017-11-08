#include "Cicdf.h"


#define ZERO_TOLERANCE 0.000001F

Cicdf::Cicdf() :
	intensityMin(0.0),
	intensityMax(1.0) {
}

Cicdf::Cicdf(intensity_t min, intensity_t max) :
	intensityMin(min),
	intensityMax(max) {
}

void Cicdf::addRegion(
	intensity_t  i_min, intensity_t  i_max,
	percentage_t p_min, percentage_t p_max
) {
	intensity_t  i_last;
	percentage_t p_last;
	if (regions.empty()) {
		i_last = intensityMin;
		p_last = percentageMin;
	} else {
		CicdfRegion &region = regions.back();
		i_last = region.intensityMax;
		p_last = region.percentageMax;
	}
	if (i_last < i_min || p_last < p_min) {
		regions.emplace_back(i_last, i_min, p_last, p_min);
	}
	regions.emplace_back(i_min, i_max, p_min, p_max);
}

Cicdf::intensity_t Cicdf::intensityAt(percentage_t percentage) const {
	for (int i = 0; i < regions.size(); i++) {
		if (regions[i].percentageMin <= percentage && percentage <= regions[i].percentageMax) {
			return regions[i].intensityAt(percentage);
		}
	}
}

Cicdf::percentage_t Cicdf::percentageAt(intensity_t intensity) const {
	for (int i = 0; i < regions.size(); i++) {
		if (regions[i].intensityMin <= intensity && intensity <= regions[i].intensityMax) {
			return regions[i].percentageAt(intensity);
		}
	}
}
