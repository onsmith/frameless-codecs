#pragma once

#include "Yuv444pFrame.h"
#include "Yuv422pFrame.h"
#include "Yuv420pFrame.h"
#include "GrayDoubleFrame.h"
#include "Gray16leFrame.h"

#include <fstream>
using std::istream;
using std::ostream;


/**
 * A Frame is an abstract class that represents a single video frame which
 *   holds intensity data. The organization, type, and format of the intensity
 *   data is specified by the concrete subclasses of this class.
 */
class Frame {
private:
	/*
	** Stores the width and height of the frame.
	*/
	int width_, height_;


protected:
	/*
	** Constructor.
	*/
	Frame(int width, int height);

	/*
	** Resize the frame.
	*/
	void resize(int width, int height);


public:
	/*
	** Gets the width of the frame.
	*/
	int width() const;

	/*
	** Gets the height of the frame.
	*/
	int height() const;

	/*
	** Reads data from an istream directly into the frame.
	*/
	virtual bool readFrom(istream&) = 0;

	/*
	** Writes the frame data directly into an ostream.
	*/
	virtual void writeTo(ostream&) = 0;

	/*
	** Make the assignment operator virtual for frame transcoding.
	*/
	//virtual Frame& operator=(Frame& const) = default;

	/*
	** Base classes should always have a virtual destructor.
	*/
	virtual ~Frame() = default;
};
