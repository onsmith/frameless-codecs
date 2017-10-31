#pragma once

#include <fstream>
using std::istream;
using std::ostream;

#include <cstdint>


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


public:
	/*
	** Plane index constants.
	*/
	const static int    Y_PLANE = 0;
	const static int    U_PLANE = 1;
	const static int    V_PLANE = 2;
	const static int LUMA_PLANE = Y_PLANE;

	/*
	** Changes the dimensions of the frame.
	*/
	virtual void resize(int width, int height);

	/*
	** Gets the width of the frame.
	*/
	int width() const;

	/*
	** Gets the height of the frame.
	*/
	int height() const;

	/*
	** Gets the number of intensities stored by the frame.
	*/
	virtual size_t size() const = 0;

	/*
	** Methods to get an intensity value by specifying its location in the frame.
	*/
	virtual uint8_t  getIntensityAsByte  (int plane, int x, int y) = 0;
	virtual uint16_t getIntensityAs16Bits(int plane, int x, int y) = 0;
	virtual double   getIntensityAsDouble(int plane, int x, int y) = 0;

	/*
	** Overload copy assignment operator.
	*/
	virtual Frame& operator=(Frame& src) = 0;

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
