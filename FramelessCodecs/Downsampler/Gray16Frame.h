#pragma once

#include <stdint.h>


class Gray16Frame {
	/*
	 ** The width and height of the frame.
	 */
	unsigned int width, height;
	
	/*
	 ** The index of the frame.
	 */
	unsigned int index;

	/*
	 ** The array that holds the frame data.
	 */
	uint16_t *data;

	/*
	** Private constructor function.
	*/
	void initialize(const unsigned int, const unsigned int, const unsigned int);


public:
	Gray16Frame(const unsigned int, const unsigned int, const unsigned int);
	Gray16Frame(const unsigned int, const unsigned int);
	~Gray16Frame();
};
