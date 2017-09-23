#define _CRT_SECURE_NO_DEPRECATE

#include "stdlib.h"
#include "string.h"
#include "stdint.h"
#include "stdio.h"
#include "assert.h"

#include "frame.h"


#define PRINT_UPDATE_EVERY_X_FRAMES 30


/*
** Converts a gray16le frame to a yuv444p frame.
*/
void gray16le_to_yuv444p(frame_t* src, frame_t* dst) {
	assert(src->width  == dst->width);
	assert(src->height == dst->height);
	assert(src->format == FRAME_FORMAT_GRAY16LE);
	assert(dst->format == FRAME_FORMAT_YUV444P);

	const int num_pixels = src->width * src->height;
	uint16_t *src_data = src->data;
	uint8_t  *dst_data = dst->data;

	// Luma
	for (int i = 0; i < num_pixels; i++) {
		dst_data[i] = (uint8_t) (src_data[i] >> 8);
	}

	// U (chroma)
	for (int i = 0; i < num_pixels; i++) {
		dst_data[num_pixels + i] = 0x80;
	}

	// V (chroma)
	for (int i = 0; i < num_pixels; i++) {
		dst_data[2 * num_pixels + i] = 0x80;
	}
}


/*
** Converts a yuv444p frame to a yuv422p frame.
*/
void yuv444p_to_yuv422p(frame_t* src, frame_t* dst) {
	assert(src->width  == dst->width);
	assert(src->height == dst->height);
	assert(src->format == FRAME_FORMAT_YUV444P);
	assert(dst->format == FRAME_FORMAT_YUV422P);

	const int num_pixels = src->width * src->height;
	uint8_t *src_y = src->data;
	uint8_t *src_u = &src_y[num_pixels]; /* skip num_pixels for Y plane */
	uint8_t *src_v = &src_u[num_pixels]; /* skip num_pixels for U plane */
	
	uint8_t *dst_y = dst->data;
	uint8_t *dst_u = &dst_y[num_pixels];     /* skip num_pixels   for Y plane */
	uint8_t *dst_v = &dst_u[num_pixels / 2]; /* skip num_pixels/2 for U plane */

	// Luma
	memcpy(dst_y, src_y, num_pixels);

	// U (chroma)
	for (int i = 0; i < num_pixels / 2; i++) {
		dst_u[i] = src_u[2 * i];
	}

	// V (chroma)
	for (int i = 0; i < num_pixels / 2; i++) {
		dst_v[i] = src_v[2 * i];
	}
}


/*
** Converts a yuv444p frame to a yuv420p frame.
*/
void yuv444p_to_yuv420p(frame_t* src, frame_t* dst) {
	assert(src->width  == dst->width);
	assert(src->height == dst->height);
	assert(src->format == FRAME_FORMAT_YUV444P);
	assert(dst->format == FRAME_FORMAT_YUV420P);

	const int num_pixels = src->width * src->height;
	uint8_t *src_y = src->data;
	uint8_t *src_u = &src_y[num_pixels]; /* skip num_pixels for Y plane */
	uint8_t *src_v = &src_u[num_pixels]; /* skip num_pixels for U plane */
	
	uint8_t *dst_y = dst->data;
	uint8_t *dst_u = &dst_y[num_pixels];     /* skip num_pixels   for Y plane */
	uint8_t *dst_v = &dst_u[num_pixels / 4]; /* skip num_pixels/4 for U plane */

	// Y (luma)
	memcpy(dst_y, src_y, num_pixels);

	// U (chroma)
	for (int i = 0; i < num_pixels / 4; i++) {
		dst_u[i] = src_u[((2 * i) % src->width) + 2 * src->width * ((2 * i) / src->width)];
	}

	// V (chroma)
	for (int i = 0; i < num_pixels / 4; i++) {
		dst_v[i] = src_v[((2 * i) % src->width) + 2 * src->width*((2 * i) / src->width)];
	}
}


/*
** Copies a given frame, converting it to yuv444p format.
*/
void convert_to_yuv444p(frame_t* src, frame_t* dst) {
	switch (src->format) {
	case (FRAME_FORMAT_GRAY16LE):
		gray16le_to_yuv444p(src, dst);
		break;
	case (FRAME_FORMAT_YUV444P):
		copy_frame(src, dst);
		break;
	}
}


/*
** Copies a given frame, converting it out of yuv444p format.
*/
void convert_from_yuv444p(frame_t* src, frame_t* dst) {
	switch (dst->format) {
	case (FRAME_FORMAT_YUV444P):
		copy_frame(src, dst);
		break;
	case (FRAME_FORMAT_YUV422P):
		yuv444p_to_yuv422p(src, dst);
		break;
	case (FRAME_FORMAT_YUV420P):
		yuv444p_to_yuv420p(src, dst);
		break;
	}
}


/*
** Prints the program usage to the standard output stream.
*/
void print_usage(char* filename) {
	printf("Usage: %s input-filename output-filename frame-width frame-height input-format output-format\n", filename);
}


/*
** Defines the entry point for the console application.
*/
int main(int argc, char *argv[]) {
	// Parse command line arguments
	char *input_filename, *output_filename;
	int frame_width, frame_height;
	frame_format_t input_format, output_format;
	if (argc == 7) {
		input_filename  = argv[1];
		output_filename = argv[2];
		frame_width     = atoi(argv[3]);
		frame_height    = atoi(argv[4]);
		input_format    = lookup_frame_format(argv[5]);
		output_format   = lookup_frame_format(argv[6]);
	}
	else {
		fprintf(stderr, "Incorrect number of arguments.\n");
		print_usage(argv[0]);
		exit(1);
	}

	// Validate input and output formats
	if (input_format != FRAME_FORMAT_GRAY16LE && input_format != FRAME_FORMAT_YUV444P) {
		fprintf(stderr, "Unrecognized input format.\n");
		fprintf(stderr, "Valid values are: gray16le, yuv444p\n");
		exit(1);
	}
	if (output_format == FRAME_FORMAT_GRAY16LE || output_format == FRAME_FORMAT_UNKNOWN) {
		fprintf(stderr, "Unrecognized output format.\n");
		fprintf(stderr, "Valid values are: yuv420p, yuv422p, yuv444p\n");
		exit(1);
	}

	// Allocate frames
	frame_t *input_frame  = create_frame(input_format,         frame_width, frame_height);
	frame_t *mid_frame    = create_frame(FRAME_FORMAT_YUV444P, frame_width, frame_height);
	frame_t *output_frame = create_frame(output_format,        frame_width, frame_height);

	// Open input/output files
	FILE *input_file  = fopen(input_filename,  "rb");
	FILE *output_file = fopen(output_filename, "wb");

	// Loop through frames and perform format conversion
	int frame_count = 0,
	    input_frame_length  = sizeof_frame_data(input_frame),
	    output_frame_length = sizeof_frame_data(output_frame);
	while (fread(input_frame->data, 1, input_frame_length, input_file) == input_frame_length) {
		if ((frame_count + 1) % PRINT_UPDATE_EVERY_X_FRAMES == 0) {
			printf("Encoding frame %i...\n", frame_count + 1);
		}
		convert_to_yuv444p(input_frame, mid_frame);
		convert_from_yuv444p(mid_frame, output_frame);
		fwrite(output_frame->data, 1, output_frame_length, output_file);
		frame_count++;
	}

	// Close files
	fclose(input_file);
	fclose(output_file);

	// Free memory
	destroy_frame(input_frame);
	destroy_frame(mid_frame);
	destroy_frame(output_frame);

	// Report results
	printf("%i frames successfully converted.\n", frame_count);
	system("pause");

	// All done
	return 0;
}
