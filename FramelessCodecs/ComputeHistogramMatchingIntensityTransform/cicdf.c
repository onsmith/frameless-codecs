#include "cicdf.h"


cicdf_region_t* create_cicdf_region(const cicdf_percentage_t min_percentage,
                                    const cicdf_percentage_t max_percentage,
                                    const cocdf_intensity_t  min_intensity,
                                    const cocdf_intensity_t  max_intensity) {
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
}


void destroy_cicdf(cicdf_t* cicdf) {
	for (int i=0; i<cicdf->num_regions; i++) {
		destroy_cicdf_region(cicdf->regions[i]);
	}
	free(cicdf->regions);
	free(cicdf);
}


static void expand_cicdf_region_array(cicdf_t* cicdf) {
	while (cicdf->num_regions >= cicdf->num_allocated_regions) {
		cicdf->num_allocated_regions *= 2;
		cicdf->regions = realloc(cicdf->regions, cicdf->num_allocated_regions * sizeof(cicdf_region_t*));
	}
}


void add_region_to_cicdf(cicdf_t* cicdf, cicdf_region_t* hroi) {
	expand_cicdf_region_array(cicdf);
	cicdf->regions[cicdf->num_regions] = hroi;
	cicdf->num_regions++;
}


cocdf_intensity_t calculate_hroi_intensity(cicdf_t* cicdf, cicdf_percentage_t percentage) {
	return 0;
}
