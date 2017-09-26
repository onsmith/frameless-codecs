#ifndef HROI_H
#define HROI_H


typedef float hroi_percentage_t;
typedef float hroi_intensity_t;


/*
** Encapsulates the data specifying a histogram region of interest (hroi).
*/
typedef struct hroi_t {
	hroi_percentage_t y_min, y_max;
	hroi_intensity_t  x_min, x_max;
} hroi_t;


/*
** Hroi constructor.
*/
hroi_t* create_hroi(const hroi_percentage_t y_min,
                    const hroi_percentage_t y_max,
                    const hroi_intensity_t  x_min,
                    const hroi_intensity_t  x_max);


/*
** Hroi destructor.
*/
void destroy_hroi(hroi_t* roi);


/*
** Hroi copy function.
*/
void copy_hroi(const hroi_t* src, hroi_t* dst);


/*
** Encapsulates a collection of hrois.
*/
typedef struct hroi_cdf_t {
	hroi_t **data;
	unsigned int allocated_elements;
	unsigned int num_hrois;
} hroi_cdf_t;


/*
** Hroi_cdf constructor.
*/
hroi_cdf_t* create_hroi_cdf();


/*
** Hroi destructor.
*/
void destroy_hroi_cdf(hroi_cdf_t* hroi_cdf);


/*
** Adds a new hroi to a hroi_cdf.
*/
void add_to_hroi_cdf(hroi_cdf_t* hroi_cdf, hroi_t* hroi);


hroi_intensity_t calculate_hroi_intensity(hroi_cdf_t* hroi_cdf, hroi_percentage_t percentage);


#endif
