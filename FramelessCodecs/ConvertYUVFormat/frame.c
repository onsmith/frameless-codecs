#include "stdlib.h"
#include "stdint.h"
#include "string.h"
#include "assert.h"

#include "frame.h"


static void set_frame_planes(frame_t* frame) {
	const int pixel_count = frame->width * frame->height;
	switch(frame->format) {
	case (FRAME_FORMAT_GRAY16LE):
		frame->plane[0] = frame->data;
		frame->plane[1] = frame->data;
		frame->plane[2] = frame->data;
		break;
	case (FRAME_FORMAT_YUV444P):
		frame->plane[0] = frame->data;
		frame->plane[1] = &((uint8_t*) frame->plane[0])[pixel_count];
		frame->plane[2] = &((uint8_t*) frame->plane[1])[pixel_count];
		break;
	case (FRAME_FORMAT_YUV422P):
		frame->plane[0] = frame->data;
		frame->plane[1] = &((uint8_t*) frame->plane[0])[pixel_count];
		frame->plane[2] = &((uint8_t*) frame->plane[1])[pixel_count / 2];
		break;
	case (FRAME_FORMAT_YUV420P):
		frame->plane[0] = frame->data;
		frame->plane[1] = &((uint8_t*) frame->plane[0])[pixel_count];
		frame->plane[2] = &((uint8_t*) frame->plane[1])[pixel_count / 4];
		break;
	}
}


frame_t* create_frame(const frame_format_t format, const int width, const int height, const int index) {
	frame_t *frame = malloc(sizeof(frame_t));
	frame->format = format;
	frame->width  = width;
	frame->height = height;
	frame->index  = index;
	frame->data = malloc(sizeof_frame_data(frame));
	set_frame_planes(frame);
	return frame;
}


void destroy_frame(frame_t* frame) {
	free(frame->data);
	free(frame);
}


void copy_frame(const frame_t* src, frame_t* dst) {
	assert(src->width  == dst->width);
	assert(src->height == dst->height);
	assert(src->format == dst->format);
	memcpy(dst->data, src->data, sizeof_frame_data(src));
}


size_t sizeof_frame_data(const frame_t* frame) {
	switch (frame->format) {
	case (FRAME_FORMAT_YUV444P):
		return sizeof(uint8_t) * frame->width * frame->height * 3;
	case (FRAME_FORMAT_YUV422P):
		return sizeof(uint8_t) * frame->width * frame->height * 2;
	case (FRAME_FORMAT_YUV420P):
		return sizeof(uint8_t) * frame->width * frame->height * 3 / 2;
	case (FRAME_FORMAT_GRAY16LE):
		return sizeof(uint16_t) * frame->width * frame->height;
	default:
		return -1;
	}
}


frame_format_t lookup_frame_format(const char* video_format_string) {
	if (strcmp(video_format_string, "gray16le") == 0) {
		return FRAME_FORMAT_GRAY16LE;
	} else if (strcmp(video_format_string, "yuv420p") == 0) {
		return FRAME_FORMAT_YUV420P;
	} else if (strcmp(video_format_string, "yuv422p") == 0) {
		return FRAME_FORMAT_YUV422P;
	} else if (strcmp(video_format_string, "yuv444p") == 0) {
		return FRAME_FORMAT_YUV444P;
	} else {
		return FRAME_FORMAT_UNKNOWN;
	}
}
