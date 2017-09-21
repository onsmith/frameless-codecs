#define _CRT_SECURE_NO_DEPRECATE

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "stdint.h"


/**
 * Prints the program usage to the standard output stream.
 */
void print_usage(char *filename) {
	printf("Usage: %s input-filename output-filename frame-width frame-height input-format output-format\n", filename);
}


/**
 * Ensures that the input format is valid.
 */
void validate_input_format(char *input_format) {
	if (strcmp(input_format, "gray16le") == 0) {
	} else {
		fprintf(stderr, "Unrecognized input format.\n");
		fprintf(stderr, "Valid values are: gray16le\n");
		exit(1);
	}
}


/**
 * Ensures that the output format is valid.
 */
void validate_output_format(char *output_format) {
	if (strcmp(output_format, "yuv420p") == 0) {
	} else if (strcmp(output_format, "yuv422p") == 0) {
	} else if (strcmp(output_format, "yuv444p") == 0) {
	} else {
		fprintf(stderr, "Unrecognized input format.\n");
		fprintf(stderr, "Valid values are: gray16le\n");
		exit(1);
	}
}


/**
 * Calculates the size of a frame.
 */
size_t frame_size(const char *frame_format, const int frame_width, const int frame_height) {
	if (strcmp(frame_format, "yuv444") == 0) {
		return sizeof(uint8_t) * frame_width * frame_height * 3;
	} else if (strcmp(frame_format, "yuv422") == 0) {
		return sizeof(uint8_t) * frame_width * frame_height * 2;
	} else if (strcmp(frame_format, "yuv420") == 0) {
		return sizeof(uint8_t) * frame_width * frame_height * 3 / 2;
	} else if (strcmp(frame_format, "gray16le") == 0) {
		return sizeof(uint16_t) * frame_width * frame_height;
	} else {
		return -1;
	}
}


/**
 * Allocates memory for a frame.
 */
void *malloc_frame(const char *frame_format, const int frame_width, const int frame_height) {
	return malloc(frame_size(frame_format, frame_width, frame_height));
}


/**
 * Converts a gray16le frame to a yuv444p frame.
 */
void gray16le_to_yuv444p(uint8_t *output_frame, uint16_t *input_frame, const int num_pixels) {
	// Luma
	for (int i = 0; i < num_pixels; i++) {
		output_frame[i] = (uint8_t)(input_frame[i] >> 8);
	}

	// U (chroma)
	for (int i = 0; i < num_pixels; i++) {
		output_frame[num_pixels + i] = 0x80;
	}

	// V (chroma)
	for (int i = 0; i < num_pixels; i++) {
		output_frame[2 * num_pixels + i] = 0x80;
	}
}


/**
 * Converts a yuv444p frame to a yuv422p frame.
 */
void yuv444p_to_yuv422p(uint8_t *output_frame, uint8_t *input_frame, const int num_pixels) {
	// Luma
	memcpy(output_frame, input_frame, num_pixels);

	// U (chroma)
	for (int i = 0; i < num_pixels / 2; i++) {
		output_frame[num_pixels + i] = input_frame[num_pixels + 2 * i];
	}

	// V (chroma)
	for (int i = 0; i < num_pixels / 2; i++) {
		output_frame[num_pixels * 3 / 2 + i] = input_frame[2 * num_pixels + 2 * i];
	}
}


/**
 * Converts a yuv444p frame to a yuv420p frame.
 */
void yuv444p_to_yuv420p(uint8_t *output_frame, uint8_t *input_frame, const int frame_width, const int frame_height) {
	const int num_pixels = frame_width * frame_height;

	// Y (luma)
	memcpy(output_frame, input_frame, num_pixels);

	// U (chroma)
	for (int i = 0; i < num_pixels / 4; i++) {
		output_frame[num_pixels + i] = input_frame[num_pixels + ((2 * i) % frame_width) + 2 * frame_width * ((2 * i) / frame_width)];
	}

	// V (chroma)
	for (int i = 0; i < num_pixels / 4; i++) {
		output_frame[num_pixels * 5 / 4 + i] = input_frame[2 * num_pixels + ((2 * i) % frame_width) + 2 * frame_width*((2 * i) / frame_width)];
	}
}


/**
 * Defines the entry point for the console application.
 */
int main(int argc, char *argv[]) {
	// Parse arguments
	char *input_filename, *output_filename, *input_format, *output_format;
	int frame_width, frame_height;
	if (argc == 7) {
		input_filename  = argv[1];
		output_filename = argv[2];
		frame_width     = atoi(argv[3]);
		frame_height    = atoi(argv[4]);
		input_format    = argv[5];
		output_format   = argv[6];
	}
	else {
		fprintf(stderr, "Incorrect number of arguments.\n");
		print_usage(argv[0]);
		exit(1);
	}

	// Validate input and output formats
	validate_input_format(input_format);
	validate_output_format(output_format);

	// Allocate frame buffers
	const int num_pixels = frame_width*frame_height;
	uint16_t *input_frame  = malloc_frame("gray16le", frame_width, frame_height);
	uint8_t  *output_frame = malloc_frame("yuv444",   frame_width, frame_height);

	// Open input/output files
	FILE *input_file  = fopen(input_filename,  "rb");
	FILE *output_file = fopen(output_filename, "wb");

	// Loop through frames and perform format conversion
	int frame_count = 0;
	while (fread(input_frame, sizeof(*input_frame), num_pixels, input_file) == num_pixels) {
		gray16le_to_yuv444p(output_frame, input_frame, num_pixels);
		fwrite(output_frame, sizeof(*output_frame), num_pixels * 3, output_file);
		frame_count++;
	}

	// Close files
	fclose(input_file);
	fclose(output_file);

	// Free memory
	free(input_frame);
	free(output_frame);

	// Report results
	printf("%i frames converted.\n", frame_count);
	system("pause");

	// All done
	return 0;
}
