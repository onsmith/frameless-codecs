#ifndef CICDF_H
#define CICDF_H


typedef double cicdf_percentage_t;
typedef double cicdf_intensity_t;


/*
** Encapsulates the data specifying a continuous intensity cdf region of
**   interest (cicdf_region).
*/
typedef struct cicdf_region_t {
	cicdf_percentage_t min_percentage, max_percentage;
	cicdf_intensity_t  min_intensity, max_intensity;
} cicdf_region_t;


/*
** Cicdf region constructor.
*/
cicdf_region_t* create_cicdf_region(const cicdf_percentage_t min_percentage,
                                    const cicdf_percentage_t max_percentage,
                                    const cicdf_intensity_t  min_intensity,
                                    const cicdf_intensity_t  max_intensity);


/*
** Cicdf region destructor.
*/
void destroy_cicdf_region(cicdf_region_t* cicdf_region);


/*
** Cicdf region copy function.
*/
void copy_cicdf_region(const cicdf_region_t* src, cicdf_region_t* dst);


/*
** Encapsulates a continuous intensity cdf (cicdf), composed of a series of
**   individual cicdf regions.
*/
typedef struct cicdf_t {
	unsigned int num_allocated_regions;
	unsigned int num_regions;
	cicdf_region_t **regions;
} cicdf_t;


/*
** Cicdf constructor.
*/
cicdf_t* create_cicdf();


/*
** Cicdf destructor.
*/
void destroy_cicdf(cicdf_t* hroi_cdf);


/*
** Adds a new region to a cicdf.
*/
void add_region_to_cicdf(cicdf_t* cicdf,
	const cicdf_percentage_t min_percentage,
	const cicdf_percentage_t max_percentage,
	const cicdf_intensity_t  min_intensity,
	const cicdf_intensity_t  max_intensity);


/*
** Computes the intensity corresponding to a given percentage for a given
**   cicdf.
*/
cicdf_intensity_t inverse_cicdf(cicdf_t* cicdf, cicdf_percentage_t percentage);


#endif
