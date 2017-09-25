#define _CRT_SECURE_NO_DEPRECATE

#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"
#include "assert.h"

#include "hroi.h"


typedef uint32_t histogram_bin_t;


/*
** Internal method to read a histogram file.
*/
static histogram_bin_t* read_histogram_file(const char* filename) {
	FILE *file = fopen(filename, "r");
	unsigned int allocated_elements = 8;
	histogram_bin_t *histogram = malloc(allocated_elements * sizeof(histogram_bin_t));
	for (int i = 0, value_buffer; fscanf(file, "%d", &value_buffer) != 0; i++) {
		while (i >= allocated_elements) {
			allocated_elements *= 2;
			histogram = realloc(histogram, allocated_elements * sizeof(histogram_bin_t));
		}
		histogram[i] = value_buffer;
	}
	fclose(file);
	return histogram;
}


/*
** Validates the passed array specifying the histogram regions of interest.
*/
void validate_rois(const hroi_intensity_t** rois, unsigned int number_of_rois) {
	hroi_percentage_t percentage_of_intensities_specified = 0.0F;
	hroi_intensity_t max_intensity_specified = 0.0F;
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
	printf("Usage: %s histogram-filename roi-filename output-filename \n", filename);
}


/**
 * Defines the entry point for the console application.
 */
int main(int argc, char *argv[]) {
	// Parse arguments
	char *histogram_filename,
	     *roi_filename,
	     *output_filename;
	if (argc == 4) {
		histogram_filename = argv[1];
		roi_filename       = argv[2];
		output_filename    = argv[3];
	} else {
		fprintf(stderr, "Incorrect number of arguments.\n");
		print_usage(argv[0]);
		exit(1);
	}

	// Read histogram file
	histogram_bin_t *histogram = read_histogram_file(histogram_filename);


	// Read roi file

	//

	// All done
	return 0;
}
