#define _CRT_SECURE_NO_DEPRECATE

#include "stdlib.h"
#include "string.h"
#include "stdint.h"
#include "stdio.h"

#include "ConvertYUVFormat/frame.h"


#define OUTPUT_BIT_WIDTH            16
#define PRINT_UPDATE_EVERY_X_FRAMES 30


/*
** Internal routine to load the transformation map from a given file.
*/
static uint16_t* load_map_from_file(const char* map_file_name) {
	const int map_length = (0x1 << OUTPUT_BIT_WIDTH);
	uint16_t *map = malloc(map_length * sizeof(uint16_t));
	FILE *map_file = fopen(map_file_name, "rb");
	fread(map_file, sizeof(uint16_t), map_length, map_file);
	fclose(map_file);
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
	uint16_t *map = load_map_from_file(map_filename);

	// Allocate frames
	frame_t *frame = create_frame(FRAME_FORMAT_GRAY16LE, frame_width, frame_height, 0);

	// Open input/output files
	FILE *input_file  = fopen(input_filename,  "rb");
	FILE *output_file = fopen(output_filename, "wb");

	// Loop through frames and apply mapping
	int frame_count = 0;
	int num_pixels = frame_width * frame_height;
	size_t frame_length = sizeof_frame_data(frame);
	uint16_t *frame_data = frame->data;
	while (fread(frame_data, 1, frame_length, input_file) == frame_length) {
		if ((frame_count + 1) % PRINT_UPDATE_EVERY_X_FRAMES == 0) {
			printf("Mapping frame %i...\n", frame_count + 1);
		}
		for (int i = 0; i < num_pixels; i++) {
			frame_data[i] = map[frame_data[i]];
		}
		fwrite(frame->data, 1, frame_length, output_file);
		frame_count++;
	}

	// Close files
	fclose(input_file);
	fclose(output_file);

	// Free memory
	destroy_frame(frame);
	free(map);

	// Report results
	printf("%i frames successfully transformed.\n", frame_count);
	system("pause");

	// All done
	return 0;
}
