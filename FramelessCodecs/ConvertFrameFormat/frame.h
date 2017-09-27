#ifndef FRAME_H
#define FRAME_H


/*
** Enumerates the different ways frame data may be formatted.
*/
typedef enum frame_format_t {
	FRAME_FORMAT_UNKNOWN,
	FRAME_FORMAT_GRAY16LE, /* 16 bits per value, luma only, little endian   */
	FRAME_FORMAT_YUV420P,  /* 8 bits per value, yuv, 420 chroma subsampling */
	FRAME_FORMAT_YUV422P,  /* 8 bits per value, yuv, 422 chroma subsampling */
	FRAME_FORMAT_YUV444P   /* 8 bits per value, yuv, no chroma subsampling  */
} frame_format_t;


/*
** Encapsulates a single frame of raw video data in a specified format.
*/
typedef struct frame_t {
	frame_format_t format; /* specifies the format of the data array   */
	int width, height;     /* the width and height of the frame        */
	int index;             /* the index of the frame within the video  */
	void *plane[3];        /* pointers to each plane in the data array */
	void *regions;            /* the data array                           */
} frame_t;


/*
** Frame constructor.
*/
frame_t* create_frame(const frame_format_t format, const int width, const int height, const int index);


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