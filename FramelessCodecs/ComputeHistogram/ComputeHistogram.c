#define _CRT_SECURE_NO_DEPRECATE

#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"


// valid range is [1, 16]
#define HIST_PIXEL_BIT_DEPTH 8
#define HIST_LENGTH          (0x1 << HIST_PIXEL_BIT_DEPTH)


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

	// Allocate histogram, tracking parameters
	int frame_size  = frame_width*frame_height,
	    frame_count = 0;
	uint32_t *histogram = calloc(HIST_LENGTH, sizeof(uint32_t));

	// Open file, allocate buffer
	uint16_t *frame = malloc(frame_size * sizeof(uint16_t));
	FILE *input_file = fopen(input_filename, "rb");

	// Loop through file and accumulate histogram
	while (fread(frame, sizeof(*frame), frame_size, input_file) == frame_size) {
		frame_count++;
		for (int i = 0; i < frame_size; i++) {
			histogram[frame[i] >> (16 - HIST_PIXEL_BIT_DEPTH)]++;
		}
	}

	// Close file
	fclose(input_file);

	// Free frame memory
	free(frame);

	// Output results
	for (int i = 0; i < HIST_LENGTH; i++) {
		printf("%i\n", histogram[i]);
	}
	printf("%i frames analyzed.\n", frame_count);

	// Free histogram memory
	free(histogram);

	// All done
	system("pause");
	return 0;
}
