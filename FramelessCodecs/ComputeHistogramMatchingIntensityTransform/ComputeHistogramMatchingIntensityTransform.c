#define _CRT_SECURE_NO_DEPRECATE

#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"
#include "assert.h"

#include "cicdf.h"


#define HISTOGRAM_SIZE (0x1 << 8)

typedef uint32_t histogram_bin_t;


/*
** Internal method to read a histogram file.
*/
static histogram_bin_t* read_histogram_file(const char* filename) {
	FILE *file = fopen(filename, "r");
	histogram_bin_t *histogram = malloc(HISTOGRAM_SIZE * sizeof(histogram_bin_t));
	for (int i = 0, buffer; i < HISTOGRAM_SIZE && fscanf(file, "%d", &buffer) == 1; i++) {
		histogram[i] = buffer;
	}
	fclose(file);
	return histogram;
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

	// Convert histogram to cdf
	cicdf_percentage_t *cdf = malloc(HISTOGRAM_SIZE * sizeof(cicdf_percentage_t));
	cdf[0] = histogram[0];
	for (int i = 1; i < HISTOGRAM_SIZE; i++) {
		cdf[i] = cdf[i-1] + histogram[i];
	}
	const cicdf_percentage_t largest_cdf_bin = cdf[HISTOGRAM_SIZE-1];
	for (int i = 0; i < HISTOGRAM_SIZE; i++) {
		cdf[i] = cdf[i] / largest_cdf_bin;
	}

	// Free histogram; we don't need it anymore
	free(histogram);

	// Read cicdf file
	FILE *cicdf_file = fopen(cicdf_filename, "r");
	cicdf_t *cicdf = create_cicdf();
	cicdf_region_t region;
	while (fscanf(cicdf_file, "%lf %lf %lf %lf", &region.min_percentage, &region.max_percentage, &region.min_intensity, &region.max_intensity) == 4) {
		if (cicdf->num_regions == 0) {
			if (region.min_intensity > 0.0F || region.min_percentage > 0.0F) {
				add_region_to_cicdf(cicdf, 0.0F, region.min_percentage, 0.0F, region.min_intensity);
			}
		} else {
			const cicdf_region_t *prev_region = cicdf->regions[cicdf->num_regions - 1];
			if (prev_region->max_percentage < region.min_percentage || prev_region->max_intensity < region.min_intensity) {
				add_region_to_cicdf(cicdf, prev_region->max_percentage, region.min_percentage, prev_region->max_intensity, region.min_intensity);
			}
		}
		add_region_to_cicdf(cicdf, region.min_percentage, region.max_percentage, region.min_intensity, region.max_intensity);
	}
	fclose(cicdf_file);

	// Complete the cicdf
	if (cicdf->num_regions == 0) {
		add_region_to_cicdf(cicdf, 0.0F, 1.0F, 0.0F, 1.0F);
	} else if (region.max_percentage < 1.0F || region.max_intensity < 1.0F) {
		add_region_to_cicdf(cicdf, region.max_percentage, 1.0F, region.max_intensity, 1.0F);
	}

	// Perform histogram matching
	cicdf_intensity_t *intensity_map = malloc(HISTOGRAM_SIZE * sizeof(cicdf_intensity_t));
	for (int i = 0; i < HISTOGRAM_SIZE; i++) {
		intensity_map[i] = inverse_cicdf(cicdf, cdf[i]);
	}

	// Write results to file
	FILE *output_file = fopen(output_filename, "w");
	for (int i = 0; i < HISTOGRAM_SIZE; i++) {
		fprintf(output_file, "%0.70lf\n", intensity_map[i]);
	}
	fclose(output_file);

	// Free memory
	destroy_cicdf(cicdf);
	free(cdf);
	free(intensity_map);

	// All done
	return 0;
}
