#define _CRT_SECURE_NO_DEPRECATE

#include "stdlib.h"
#include "string.h"
#include "stdint.h"
#include "stdio.h"

#include "files.h"


#define PRINT_UPDATE_EVERY_X_FRAMES 30


typedef uint16_t input_intensity_t;
typedef uint16_t output_intensity_t;


/*
** Internal routine to read the transformation map from a given file.
*/
static output_intensity_t* read_map_file(const char* file_name) {
	FILE *file = fopen(file_name, "rb");
	output_intensity_t* map = read_entire_file(file);
	fclose(file);
	return map;
}


/*
** Prints the program usage to the standard output stream.
*/
void print_usage(char* filename) {
	printf("Usage: %s input-filename output-filename map-filename frame-width frame-height\n", filename);
}


/*
** Defines the entry point for the console application.
*/
int main(int argc, char *argv[]) {
	// Parse command line arguments
	char *input_filename, *output_filename, *map_filename;
	int frame_width, frame_height;
	if (argc == 6) {
		input_filename  = argv[1];
		output_filename = argv[2];
		map_filename    = argv[3];
		frame_width     = atoi(argv[4]);
		frame_height    = atoi(argv[5]);
	}
	else {
		fprintf(stderr, "Incorrect number of arguments.\n");
		print_usage(argv[0]);
		exit(1);
	}

	// Load map from file
	output_intensity_t *map = read_map_file(map_filename);

	// Allocate data arrays
	const int num_pixels = frame_width * frame_height;
	input_intensity_t  *input_data  = malloc(num_pixels * sizeof(input_intensity_t));
	output_intensity_t *output_data = malloc(num_pixels * sizeof(output_intensity_t));

	// Open input/output files
	FILE *input_file  = fopen(input_filename,  "rb");
	FILE *output_file = fopen(output_filename, "wb");

	// Loop through frames and apply mapping
	int frame_count = 0;
	while (fread(input_data, sizeof(input_intensity_t), num_pixels, input_file) == num_pixels) {
		if ((frame_count + 1) % PRINT_UPDATE_EVERY_X_FRAMES == 0) {
			printf("Transforming frame %i...\n", frame_count + 1);
		}
		for (int i = 0; i < num_pixels; i++) {
			output_data[i] = map[input_data[i]];
		}
		fwrite(output_data, sizeof(output_intensity_t), num_pixels, output_file);
		frame_count++;
	}

	// Close files
	fclose(input_file);
	fclose(output_file);

	// Free memory
	free(map);
	free(input_data);
	free(output_data);

	// Report results
	printf("%i frames successfully transformed.\n", frame_count);
	system("pause");

	// All done
	return 0;
}
