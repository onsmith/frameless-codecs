#include "hroi.h"


hroi_t* create_hroi(const hroi_percentage_t y_min,
                    const hroi_percentage_t y_max,
                    const hroi_intensity_t  x_min,
                    const hroi_intensity_t  x_max) {
	hroi_t* roi = malloc(sizeof(hroi_t));
	roi->y_min = y_min;
	roi->y_max = y_max;
	roi->x_min = x_min;
	roi->x_max = x_max;
	return roi;
}


void destroy_hroi(hroi_t* roi) {
	free(roi);
}


void copy_hroi(const hroi_t* src, hroi_t* dst) {
	dst->y_min = dst->y_min;
	dst->y_max = dst->y_max;
	dst->x_min = dst->x_min;
	dst->x_max = dst->x_max;
}


hroi_cdf_t* create_hroi_cdf() {
	hroi_cdf_t* hroi_cdf = malloc(sizeof(hroi_cdf_t));
	hroi_cdf->num_hrois = 0;
	hroi_cdf->allocated_elements = 8;
	hroi_cdf->data = malloc(hroi_cdf->allocated_elements * sizeof(hroi_t*));
}


void destroy_hroi_cdf(hroi_cdf_t* hroi_cdf) {
	free(hroi_cdf->data);
	free(hroi_cdf);
}


static void increment_hroi_cdf_size(hroi_cdf_t* hroi_cdf) {
	while (hroi_cdf->num_hrois >= hroi_cdf->allocated_elements) {
		hroi_cdf->allocated_elements *= 2;
		hroi_cdf->data = realloc(hroi_cdf->data, hroi_cdf->allocated_elements * sizeof(hroi_t*));
	}
}


void add_to_hroi_cdf(hroi_cdf_t* hroi_cdf, hroi_t* hroi) {
	increment_hroi_cdf_size(hroi_cdf);
	hroi_cdf->data[hroi_cdf->num_hrois] = hroi;
	hroi_cdf->num_hrois++;
}


hroi_intensity_t calculate_hroi_intensity(hroi_cdf_t* hroi_cdf, hroi_percentage_t percentage) {
	return 0;
}
