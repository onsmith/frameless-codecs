#define _CRT_SECURE_NO_DEPRECATE

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "stdint.h"


typedef enum {
	gray16le,
	yuv420p,
	yuv422p,
	yuv444p,
	unknown
} video_format;


/**
 * Lookup function to convert a video format string to a video_format enum value.
 */
video_format lookup_video_format(char *video_format_string) {
	if (strcmp(video_format_string, "gray16le") == 0) {
		return gray16le;
	} else if (strcmp(video_format_string, "yuv420p") == 0) {
		return yuv420p;
	} else if (strcmp(video_format_string, "yuv422p") == 0) {
		return yuv422p;
	} else if (strcmp(video_format_string, "yuv444p") == 0) {
		return yuv444p;
	} else {
		return unknown;
	}
}


/**
 * Prints the program usage to the standard output stream.
 */
void print_usage(char *filename) {
	printf("Usage: %s input-filename output-filename frame-width frame-height input-format output-format\n", filename);
}


/**
 * Calculates the size of a pixel.
 */
size_t pixel_size(const video_format frame_format) {
	switch (frame_format) {
	case (yuv444p):
	case (yuv422p):
	case (yuv420p):
		return sizeof(uint8_t);
	case (gray16le):
		return sizeof(uint16_t);
	default:
		return -1;
	}
}


/**
 * Calculates the size of a frame.
 */
size_t frame_size(const video_format frame_format, const int frame_width, const int frame_height) {
	switch (frame_format) {
	case (yuv444p):
		return sizeof(uint8_t) * frame_width * frame_height * 3;
	case (yuv422p):
		return sizeof(uint8_t) * frame_width * frame_height * 2;
	case (yuv420p):
		return sizeof(uint8_t) * frame_width * frame_height * 3 / 2;
	case (gray16le):
		return sizeof(uint16_t) * frame_width * frame_height;
	default:
		return -1;
	}
}


/**
 * Allocates memory for a frame.
 */
void *malloc_frame(const video_format frame_format, const int frame_width, const int frame_height) {
	return malloc(frame_size(frame_format, frame_width, frame_height));
}


/**
 * Converts a gray16le frame to a yuv444p frame.
 */
void gray16le_to_yuv444p(uint8_t *output_frame, uint16_t *input_frame, const int frame_width, const int frame_height) {
	const int num_pixels = frame_width * frame_height;

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
void yuv444p_to_yuv422p(uint8_t *output_frame, uint8_t *input_frame, const int frame_width, const int frame_height) {
	const int num_pixels = frame_width * frame_height;

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
	// Parse command line arguments
	char *input_filename, *output_filename;
	int frame_width, frame_height;
	video_format input_format, output_format;
	if (argc == 7) {
		input_filename  = argv[1];
		output_filename = argv[2];
		frame_width     = atoi(argv[3]);
		frame_height    = atoi(argv[4]);
		input_format    = lookup_video_format(argv[5]);
		output_format   = lookup_video_format(argv[6]);
	}
	else {
		fprintf(stderr, "Incorrect number of arguments.\n");
		print_usage(argv[0]);
		exit(1);
	}

	// Validate input and output formats
	if (input_format != gray16le) {
		fprintf(stderr, "Unrecognized input format.\n");
		fprintf(stderr, "Valid values are: gray16le\n");
		exit(1);
	}
	if (output_format == unknown || output_format == gray16le) {
		fprintf(stderr, "Unrecognized output format.\n");
		fprintf(stderr, "Valid values are: yuv420p, yuv422p, yuv444p\n");
		exit(1);
	}

	// Allocate frame buffers
	const int num_pixels = frame_width*frame_height;
	uint16_t *input_frame  = malloc_frame(input_format,  frame_width, frame_height);
	uint8_t  *mid_frame    = malloc_frame(yuv444p,       frame_width, frame_height);
	uint8_t  *output_frame = malloc_frame(output_format, frame_width, frame_height);

	// Open input/output files
	FILE *input_file  = fopen(input_filename,  "rb");
	FILE *output_file = fopen(output_filename, "wb");

	// Loop through frames and perform format conversion
	int frame_count = 0;
	while (fread(input_frame, sizeof(*input_frame), num_pixels, input_file) == num_pixels) {
		gray16le_to_yuv444p(mid_frame, input_frame, num_pixels);
		yuv444p_to_yuv422p(output_frame, mid_frame, frame_width, frame_height);
		fwrite(output_frame, sizeof(*output_frame), num_pixels * 3/2, output_file);
		frame_count++;
	}

	// Close files
	fclose(input_file);
	fclose(output_file);

	// Free memory
	free(input_frame);
	free(mid_frame);
	free(output_frame);

	// Report results
	printf("%i frames converted.\n", frame_count);
	system("pause");

	// All done
	return 0;
}
