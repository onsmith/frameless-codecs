#define _CRT_SECURE_NO_DEPRECATE

#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"


#define INTENSITY_BIT_SHIFT 8
#define INTENSITY_BIT_DEPTH 8
#define HISTOGRAM_NUM_BINS  (0x1 << INTENSITY_BIT_DEPTH)


typedef uint16_t intensity_t;
typedef uint32_t histogram_bin_t;


/**
 * Prints the program usage to the standard output stream.
 */
void print_usage(char *filename) {
	printf("Usage: %s input-filename\n", filename);
}


/**
 * Defines the entry point for the console application.
 */
int main(int argc, char *argv[]) {
	// Parse arguments
	char *input_filename;
	if (argc == 2) {
		input_filename = argv[1];
	} else {
		fprintf(stderr, "Incorrect number of arguments.\n");
		print_usage(argv[0]);
		getchar();
		exit(1);
	}

	// Allocate histogram
	histogram_bin_t *histogram = calloc(HISTOGRAM_NUM_BINS, sizeof(histogram_bin_t));

	// Open file
	FILE *input_file = fopen(input_filename, "rb");
	if (input_file == NULL) {
		fprintf(stderr, "File could not be opened: %s\n", input_filename);
		getchar();
		exit(1);
	}

	// Traverse file and accumulate histogram
	intensity_t buffer;
	while (fread(&buffer, sizeof(intensity_t), 1, input_file) == 1) {
		histogram[buffer >> INTENSITY_BIT_SHIFT]++;
	}

	// Close file
	fclose(input_file);

	// Output results
	for (int i = 0; i < HISTOGRAM_NUM_BINS; i++) {
		printf("%i\n", histogram[i]);
	}

	// Free histogram memory
	free(histogram);

	// All done
	return 0;
}
