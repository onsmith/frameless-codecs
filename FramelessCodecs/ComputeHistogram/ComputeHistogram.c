#define _CRT_SECURE_NO_DEPRECATE

#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"


#define INTENSITY_BIT_SHIFT 8
#define INTENSITY_BIT_DEPTH 8
#define HISTOGRAM_NUM_BINS  (0x1 << INTENSITY_BIT_DEPTH)


typedef uint16_t hroi_intensity_t;
typedef uint32_t histogram_frequency_t;


/**
 * Prints the program usage to the standard output stream.
 */
void print_usage(char *filename) {
	printf("Usage: %s input-filename frame-width frame-height\n", filename);
}


/**
 * Defines the entry point for the console application.
 */
int main(int argc, char *argv[]) {
	// Parse arguments
	char *input_filename;
	int frame_width, frame_height;
	if (argc == 4) {
		input_filename = argv[1];
		frame_width    = atoi(argv[2]);
		frame_height   = atoi(argv[3]);
	} else {
		fprintf(stderr, "Incorrect number of arguments.\n");
		print_usage(argv[0]);
		exit(1);
	}

	// Allocate histogram
	histogram_frequency_t *histogram = calloc(HISTOGRAM_NUM_BINS, sizeof(histogram_frequency_t));

	// Open file, allocate buffer
	unsigned int num_pixels = frame_width * frame_height;
	hroi_intensity_t *frame_data = malloc(num_pixels * sizeof(hroi_intensity_t));
	FILE *input_file = fopen(input_filename, "rb");

	// Loop through file and accumulate histogram
	while (fread(frame_data, sizeof(hroi_intensity_t), num_pixels, input_file) == num_pixels) {
		for (int i = 0; i < num_pixels; i++) {
			histogram[frame_data[i] >> INTENSITY_BIT_SHIFT]++;
		}
	}

	// Close file
	fclose(input_file);

	// Free frame memory
	free(frame_data);

	// Output results
	for (int i = 0; i < HISTOGRAM_NUM_BINS; i++) {
		printf("%i\n", histogram[i]);
	}

	// Free histogram memory
	free(histogram);

	// All done
	return 0;
}
