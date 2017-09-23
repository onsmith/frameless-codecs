#ifndef FRAME_H
#define FRAME_H


/*
** Enumerates the different ways frame data may be formatted.
*/
typedef enum frame_format_t {
	FRAME_FORMAT_UNKNOWN,
	FRAME_FORMAT_GRAY16LE,
	FRAME_FORMAT_YUV420P,
	FRAME_FORMAT_YUV422P,
	FRAME_FORMAT_YUV444P
} frame_format_t;


/*
** Encapsulates a single frame of raw video data in a specified format.
*/
typedef struct frame_t {
	frame_format_t format; /* specifies the format of the data array */
	int width, height;     /* width and height of the frame */
	int index;             /* index of the frame within the video */
	void *plane[3];        /* pointers to each plane in the data array */
	void *data;            /* the data array */
} frame_t;


/*
** Frame constructors.
*/
frame_t* create_frame(const frame_format_t format, const int width, const int height, const int index);
frame_t* create_frame(const frame_format_t format, const int width, const int height);


/*
** Frame destructor.
*/
void destroy_frame(frame_t* frame);


/*
** Frame copy function.
*/
void copy_frame(const frame_t* src, frame_t* dst);


/*
** Calculates the length of a frame's data array, in bytes. Returns -1 if the
**   frame format is unknown.
*/
size_t sizeof_frame_data(const frame_t* frame);


/*
** Converts a frame format string to a frame_format_t enum value.
*/
frame_format_t lookup_frame_format(const char* frame_format_string);


#endif
