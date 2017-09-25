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
                    const hroi_intensity_t x_min,
                    const hroi_intensity_t x_max);


/*
** Hroi destructor.
*/
void destroy_hroi(hroi_t* roi);


/*
** Hroi copy function.
*/
void copy_hroi(const hroi_t* src, hroi_t* dst);


#endif
