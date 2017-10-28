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
 * A Frame is an abstract class representing a single video frame which holds
 *   intensity data. Intensity representation and organization is unknown to
 *   this class, and is instead defined in subclasses.
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
	** Resize the dimensions of the frame.
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
	** Base classes should always have a virtual destructor.
	*/
	virtual ~Frame() = default;
};
