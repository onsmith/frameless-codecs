#include "stdlib.h"
#include "stdint.h"
#include "string.h"
#include "assert.h"

#include "frame.h"


frame_t* create_frame(const video_format_t format, const int width, const int height) {
	frame_t *frame = malloc(sizeof(frame_t));
	frame->format = format;
	frame->width  = width;
	frame->height = height;
	frame->data = malloc(sizeof_frame(frame));
	return frame;
};


void destroy_frame(frame_t* frame) {
	free(frame->data);
	free(frame);
};


void copy_frame(const frame_t* src, frame_t* dst) {
	assert(src->width  == dst->width);
	assert(src->height == dst->height);
	assert(src->format == dst->format);
	memcpy(dst->data, src->data, sizeof_frame(src));
};


size_t sizeof_pixel(const video_format_t frame_format) {
	switch (frame_format) {
	case (VIDEO_FORMAT_YUV444P):
	case (VIDEO_FORMAT_YUV422P):
	case (VIDEO_FORMAT_YUV420P):
		return sizeof(uint8_t);
	case (VIDEO_FORMAT_GRAY16LE):
		return sizeof(uint16_t);
	default:
		return -1;
	}
}


size_t sizeof_frame(const frame_t* frame) {
	switch (frame->format) {
	case (VIDEO_FORMAT_YUV444P):
		return sizeof_pixel(VIDEO_FORMAT_YUV444P) * frame->width * frame->height * 3;
	case (VIDEO_FORMAT_YUV422P):
		return sizeof_pixel(VIDEO_FORMAT_YUV422P) * frame->width * frame->height * 2;
	case (VIDEO_FORMAT_YUV420P):
		return sizeof_pixel(VIDEO_FORMAT_YUV420P) * frame->width * frame->height * 3 / 2;
	case (VIDEO_FORMAT_GRAY16LE):
		return sizeof_pixel(VIDEO_FORMAT_GRAY16LE) * frame->width * frame->height;
	default:
		return -1;
	}
}


video_format_t lookup_video_format(const char* video_format_string) {
	if (strcmp(video_format_string, "gray16le") == 0) {
		return VIDEO_FORMAT_GRAY16LE;
	} else if (strcmp(video_format_string, "yuv420p") == 0) {
		return VIDEO_FORMAT_YUV420P;
	} else if (strcmp(video_format_string, "yuv422p") == 0) {
		return VIDEO_FORMAT_YUV422P;
	} else if (strcmp(video_format_string, "yuv444p") == 0) {
		return VIDEO_FORMAT_YUV444P;
	} else {
		return VIDEO_FORMAT_UNKNOWN;
	}
}
