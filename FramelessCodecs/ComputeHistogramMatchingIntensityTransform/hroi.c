#include "hroi.h"


hroi_t* create_hroi(const hroi_percentage_t y_min,
                    const hroi_percentage_t y_max,
                    const hroi_intensity_t x_min,
                    const hroi_intensity_t x_max) {
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


hroi_intensity_t calculate_hroi_intensity(const hroi_t** hroi_list, const unsigned int hroi_list_length, hroi_percentage_t percentage) {
	return 0;
}
