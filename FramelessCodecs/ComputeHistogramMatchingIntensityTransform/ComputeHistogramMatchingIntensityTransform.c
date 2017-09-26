#define _CRT_SECURE_NO_DEPRECATE

#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"
#include "assert.h"

#include "cicdf.h"


typedef uint32_t histogram_bin_t;


/*
** Internal method to read a histogram file.
*/
static histogram_bin_t* read_histogram_file(const char* filename) {
	FILE *file = fopen(filename, "r");
	unsigned int num_allocated_regions = 8;
	histogram_bin_t *histogram = malloc(num_allocated_regions * sizeof(histogram_bin_t));
	for (int i = 0, value_buffer; fscanf(file, "%d", &value_buffer) == 1; i++) {
		while (i >= num_allocated_regions) {
			num_allocated_regions *= 2;
			histogram = realloc(histogram, num_allocated_regions * sizeof(histogram_bin_t));
		}
		histogram[i] = value_buffer;
	}
	fclose(file);
	return histogram;
}


/*
** Validates the passed array specifying the histogram regions of interest.
*/
void validate_rois(const cocdf_intensity_t** rois, unsigned int number_of_rois) {
	cicdf_percentage_t percentage_of_intensities_specified = 0.0F;
	cocdf_intensity_t max_intensity_specified = 0.0F;
	for (int i=0; i<number_of_rois; i++) {
		assert(0.0F <= rois[i][0]);                                       /* percentage of pixels in roi must be nonnegative */
		assert(rois[i][0] + percentage_of_intensities_specified <= 0.1F); /* can't specify more than 100% of pixels          */
		assert(max_intensity_specified <= rois[i][1]);                    /* can't overlap intensity regions                 */
		assert(rois[i][1] < rois[i][2]);                                  /* smaller intensity coordinate must come first    */
		assert(rois[i][2] <= 1.0F);                                       /* can't specify intensity region above 1.0F       */
		max_intensity_specified = rois[i][2];
		percentage_of_intensities_specified += rois[i][0];
	}
}





/**
 * Prints the program usage to the standard output stream.
 */
static void print_usage(char *filename) {
	printf("Usage: %s histogram-filename cicdf-filename output-filename \n", filename);
}


/**
 * Defines the entry point for the console application.
 */
int main(int argc, char *argv[]) {
	// Parse arguments
	char *histogram_filename,
	     *cicdf_filename,
	     *output_filename;
	if (argc == 4) {
		histogram_filename = argv[1];
		cicdf_filename     = argv[2];
		output_filename    = argv[3];
	} else {
		fprintf(stderr, "Incorrect number of arguments.\n");
		print_usage(argv[0]);
		exit(1);
	}

	// Read histogram file
	histogram_bin_t *histogram = read_histogram_file(histogram_filename);


	// Read cicdf file
	FILE *cicdf_file = fopen(cicdf_filename, "r");
	cicdf_t *cicdf = create_cicdf();
	cicdf_region_t *region = create_cicdf_region(0, 0, 0, 0);
	while (fscanf(cicdf_file, "%f %f %f %f", &region->min_percentage, &region->max_percentage, &region->min_intensity, &region->max_intensity) != 4) {
		if (cicdf->num_regions == 0) {
			if (region->min_intensity > 0 && region->min_percentage > 0) {
				add_region_to_cicdf(cicdf, create_cicdf_region(0, region->min_percentage, 0, region->min_intensity));
			}
		} else {
			const cicdf_region_t *prior_hroi = cicdf->regions[cicdf->num_regions];
			if (prior_hroi->max_percentage < region->min_percentage || prior_hroi->max_intensity < region->min_intensity) {
				add_region_to_cicdf(cicdf, create_cicdf_region(prior_hroi->max_percentage, region->min_percentage, prior_hroi->max_intensity, region->min_intensity));
			}
		}
		add_region_to_cicdf(cicdf, region);
		region = create_cicdf_region(0, 0, 0, 0);
	}
	free(region);
	fclose(cicdf_file);

	// Free memory
	destroy_cicdf(cicdf);
	free(histogram);

	// All done
	return 0;
}
