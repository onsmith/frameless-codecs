#ifndef FRAME_H
#define FRAME_H


/*
** Enumerates the different types of raw video formats.
*/
typedef enum video_format_t {
	VIDEO_FORMAT_UNKNOWN,
	VIDEO_FORMAT_GRAY16LE,
	VIDEO_FORMAT_YUV420P,
	VIDEO_FORMAT_YUV422P,
	VIDEO_FORMAT_YUV444P
} video_format_t;


/*
** Encapsulates a single frame of raw video data in a specified format.
*/
typedef struct frame_t {
	video_format_t format;
	int width, height;
	void *data;
} frame_t;


/*
** Frame constructor.
*/
frame_t* create_frame(const video_format_t format, const int width, const int height);


/*
** Frame destructor.
*/
void destroy_frame(frame_t* frame);


/*
** Frame copy function.
*/
void copy_frame(const frame_t* src, frame_t* dst);


/*
** Calculates the size of a pixel. Returns -1 if the video format is unknown.
*/
size_t sizeof_pixel(const video_format_t frame_format);


/*
** Calculates the size of a frame's data array, in bytes. Returns -1 if the
**   video format is unknown.
*/
size_t sizeof_frame(const frame_t* frame);


/*
** Converts a video format string to a video_format_t enum value.
*/
video_format_t lookup_video_format(const char* video_format_string);


#endif
