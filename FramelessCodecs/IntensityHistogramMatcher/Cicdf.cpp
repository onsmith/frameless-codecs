#include "Cicdf.h"


#define ZERO_TOLERANCE 0.000001F

Cicdf::Cicdf() :
	intensity_min(0.0),
	intensity_max(0.0) {
}

Cicdf::Cicdf(intensity_t min, intensity_t max) :
	intensity_min(min),
	intensity_max(max) {
}

void Cicdf::addRegion(intensity_t, percentage_t, intensity_t, percentage_t) {
}

void Cicdf::addRegion(intensity_t, percentage_t) {
}

Cicdf::intensity_t Cicdf::intensityAt(percentage_t percentage) const {
	for (int i = 0; i < regions.size(); i++) {
		if (regions[i].percentage_min <= percentage && percentage <= regions[i].percentage_max) {
			return regions[i].intensityAt(percentage);
		}
	}
}

Cicdf::percentage_t Cicdf::percentageAt(intensity_t intensity) const {
	for (int i = 0; i < regions.size(); i++) {
		if (regions[i].intensity_min <= intensity && intensity <= regions[i].intensity_max) {
			return regions[i].percentageAt(intensity);
		}
	}
}
