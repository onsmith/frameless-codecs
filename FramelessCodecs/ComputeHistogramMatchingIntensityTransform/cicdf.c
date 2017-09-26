#include "math.h"
#include "stdlib.h"

#include "cicdf.h"


#define ZERO_TOLERANCE 0.000001F


cicdf_region_t* create_cicdf_region(const cicdf_percentage_t min_percentage,
                                    const cicdf_percentage_t max_percentage,
                                    const cicdf_intensity_t  min_intensity,
                                    const cicdf_intensity_t  max_intensity) {
	cicdf_region_t* region = malloc(sizeof(cicdf_region_t));
	region->min_percentage = min_percentage;
	region->max_percentage = max_percentage;
	region->min_intensity  = min_intensity;
	region->max_intensity  = max_intensity;
	return region;
}


void destroy_cicdf_region(cicdf_region_t* region) {
	free(region);
}


void copy_cicdf_region(const cicdf_region_t* src, cicdf_region_t* dst) {
	dst->min_percentage = src->min_percentage;
	dst->max_percentage = src->max_percentage;
	dst->min_intensity  = src->min_intensity;
	dst->max_intensity  = src->max_intensity;
}


cicdf_t* create_cicdf() {
	cicdf_t* cicdf = malloc(sizeof(cicdf_t));
	cicdf->num_regions = 0;
	cicdf->num_allocated_regions = 8;
	cicdf->regions = malloc(cicdf->num_allocated_regions * sizeof(cicdf_region_t*));
	return cicdf;
}


void destroy_cicdf(cicdf_t* cicdf) {
	for (int i=0; i<cicdf->num_regions; i++) {
		destroy_cicdf_region(cicdf->regions[i]);
	}
	free(cicdf->regions);
	free(cicdf);
}


static void expand_cicdf_region_array(cicdf_t* cicdf) {
	while (cicdf->num_allocated_regions <= cicdf->num_regions) {
		cicdf->num_allocated_regions *= 2;
		cicdf->regions = realloc(cicdf->regions, cicdf->num_allocated_regions * sizeof(cicdf_region_t*));
	}
}


void add_region_to_cicdf(cicdf_t* cicdf,
		const cicdf_percentage_t min_percentage,
		const cicdf_percentage_t max_percentage,
		const cicdf_intensity_t  min_intensity,
		const cicdf_intensity_t  max_intensity) {
	expand_cicdf_region_array(cicdf);
	cicdf->regions[cicdf->num_regions] = create_cicdf_region(
		min_percentage, max_percentage, min_intensity, max_intensity);
	cicdf->num_regions++;
}


static inline double evaluate_cubic(const double a, const double b, const double c, const double d, const double x) {
	return a*x*x*x + b*x*x + c*x + d;
}


static double find_cubic_zero(const double a, const double b, const double c, const double d, const double x_min, const double x_max) {
	const double x_mid = (x_min + x_max) / 2;
	const double y_mid = evaluate_cubic(a, b, c, d, x_mid);
	if (y_mid < -ZERO_TOLERANCE) {
		return find_cubic_zero(a, b, c, d, x_mid, x_max);
	} else if (y_mid < ZERO_TOLERANCE) {
		return x_mid;
	} else {
		return find_cubic_zero(a, b, c, d, x_min, x_mid);
	}
}


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


static cicdf_intensity_t inverse_cicdf_region(cicdf_region_t* region, cicdf_percentage_t percentage) {
	cicdf_percentage_t midpoint_percentage = (region->max_percentage + region->min_percentage) / 2;
	cicdf_percentage_t midpoint_intensity  = (region->max_intensity  + region->min_intensity ) / 2;
	if (percentage <= midpoint_percentage) {
		const double a = a3(region->min_intensity, region->min_percentage, midpoint_intensity, midpoint_percentage, 1.0, 0.0);
		const double b = a2(region->min_intensity, region->min_percentage, midpoint_intensity, midpoint_percentage, 1.0, 0.0);
		const double c = a1(region->min_intensity, region->min_percentage, midpoint_intensity, midpoint_percentage, 1.0, 0.0);
		const double d = a0(region->min_intensity, region->min_percentage, midpoint_intensity, midpoint_percentage, 1.0, 0.0);
		return find_cubic_zero(a, b, c, d - percentage, region->min_intensity, midpoint_intensity);
	} else {
		const double a = a3(midpoint_intensity, midpoint_percentage, region->max_intensity, region->max_percentage, 0.0, 1.0);
		const double b = a2(midpoint_intensity, midpoint_percentage, region->max_intensity, region->max_percentage, 0.0, 1.0);
		const double c = a1(midpoint_intensity, midpoint_percentage, region->max_intensity, region->max_percentage, 0.0, 1.0);
		const double d = a0(midpoint_intensity, midpoint_percentage, region->max_intensity, region->max_percentage, 0.0, 1.0);
		return find_cubic_zero(a, b, c, d - percentage, midpoint_intensity, region->max_intensity);
	}
}


cicdf_intensity_t inverse_cicdf(cicdf_t* cicdf, cicdf_percentage_t percentage) {
	for (int i = 0; i < cicdf->num_regions; i++) {
		if (cicdf->regions[i]->min_percentage <= percentage && percentage <= cicdf->regions[i]->max_percentage) {
			return inverse_cicdf_region(cicdf->regions[i], percentage);
		}
	}
}
