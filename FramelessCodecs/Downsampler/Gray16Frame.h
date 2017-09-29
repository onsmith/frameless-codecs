#pragma once

#include <stdint.h>


class Gray16Frame {
public:
	/*
	** Defines which type an intensity value should be.
	*/
	typedef uint16_t intensity_t;

private:
	/*
	 ** The width and height of the frame.
	 */
	unsigned int width, height;

	/*
	 ** The raw array holding the frame data.
	 */
	intensity_t* data;

public:
	/*
	** Gets the raw array of pixel intensity values.
	*/
	intensity_t* getData();

	/*
	** Gets the raw array of luma pixel intensity values.
	*/
	intensity_t* getLuma();

	/*
	** Gets the total number of pixels in the frame.
	*/
	unsigned int getNumPixels();

	/*
	** Gets the total size of the frame array.
	*/
	size_t getDataLength();

	/*
	** Gets the intensity of the pixel located at position (x,y), where the
	**   origin is located at the top left corner of the frame, and pixels are
	**   zero-indexed.
	*/
	intensity_t getIntensity(unsigned int x, unsigned int y);

	/*
	** Gets the intensity of the pixel located at position i, where pixels are
	**   zero-indexed in row-major order.
	*/
	intensity_t getIntensity(unsigned int i);

	/*
	** Constructor
	*/
	Gray16Frame(const unsigned int, const unsigned int);

	/*
	** Copy constructor
	*/
	Gray16Frame(Gray16Frame&);

	/*
	** Destructor
	*/
	~Gray16Frame();
};
