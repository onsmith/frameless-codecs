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
	int width, height;

	/*
	 ** The raw array holding the frame data.
	 */
	intensity_t* data;

public:
	/*
	** Gets the underlying array of pixel intensity values.
	*/
	intensity_t* getData();

	/*
	** Gets the underlying array of luma pixel intensity values.
	*/
	intensity_t* getLuma();

	/*
	** Gets the total number of pixels in the frame.
	*/
	int getNumPixels() const;

	/*
	** Gets the total size of the frame array.
	*/
	size_t getDataLength() const;

	/*
	** Gets the intensity of the pixel located at position (x,y), where the
	**   origin is located at the top left corner of the frame, and pixels are
	**   zero-indexed.
	*/
	intensity_t getIntensity(int x, int y) const;

	/*
	** Gets the intensity of the pixel located at position i, where pixels are
	**   zero-indexed in row-major order.
	*/
	intensity_t getIntensity(int i) const;

	/*
	** Constructor
	*/
	Gray16Frame(const int width, const int height);

	/*
	** Copy constructor
	*/
	Gray16Frame(const Gray16Frame& obj);

	/*
	** Destructor
	*/
	~Gray16Frame();
};
