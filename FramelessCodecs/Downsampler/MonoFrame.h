#pragma once


#include "Plane.h"

#include <algorithm>
using std::copy;


template <typename intensity_t>
class MonoFrame {
private:
	/*
	** A MonoFrame encapsulates a single Plane object.
	*/
	Plane<intensity_t> plane;


	/*
	 ** This object manages its own memory.
	 */
	intensity_t* mem;


public:
	/*
	** Gets the width of the frame, in pixels.
	*/
	int width() const {
		return plane.width();
	}


	/*
	** Gets the height of the frame, in pixels.
	*/
	int height() const {
		return plane.height();
	}


	/*
	** Gets the total number of pixels in the frame.
	*/
	int numPixels() const {
		return plane.numPixels();
	}


	/*
	** Calculates the total number of intensity values stored in the plane.
	*/
	int size() const {
		return numPixels();
	}


	/*
	** Gets the underlying array of pixel intensity values.
	*/
	intensity_t* data() const {
		return mem;
	}


	/*
	** Gets the intensity of the pixel located at position i, where pixels are
	**   zero-indexed in row-major order starting from the top left of the frame.
	*/
	intensity_t& intensityAt(int i) const {
		return plane.intensityAt(i);
	}


	/*
	** Gets the intensity of the pixel located at position (x, y), where the
	**   origin is located at the top left corner of the frame, and pixels are
	**   zero-indexed.
	*/
	intensity_t& intensityAt(int x, int y) const {
		return plane.intensityAt(x, y);
	}


	/*
	** Populates the frame's intensity array by reading from a given istream.
	**   Returns true if successful.
	*/
	bool readFrom(istream& stream) {
		return plane.readFrom(stream);
	}


	/*
	** Writes the frame's intensity array to a given ostream.
	*/
	void writeTo(ostream& stream) {
		return plane.writeTo(stream);
	}


public:
	/*
	** Constructor.
	*/
	MonoFrame(int width, int height) :
		mem(new intensity_t[width * height]),
		plane(width, height) {
		plane.pointTo(mem);
	}


	/*
	** Copy constructor.
	*/
	MonoFrame(const MonoFrame<intensity_t>& obj) :
		mem(new intensity_t[obj.numPixels()]),
		plane(obj.width(), obj.height()) {
		plane.pointTo(mem);
		copy(obj.mem, obj.mem + obj.numPixels(), mem);
	}


	/*
	** Copy assignment operator.
	*/
	MonoFrame& operator=(const MonoFrame<intensity_t>& obj) {
		if (this != &obj) {
			if (numPixels() != obj.numPixels()) {
				delete mem;
				mem = new intensity_t[obj.numPixels()];
				plane.pointTo(mem);
			}
			plane.setDimensionsTo(obj.width(), obj.height());
			copy(obj.mem, obj.mem + obj.numPixels(), mem);
		}
		return *this;
	}


	/*
	** Destructor.
	*/
	~MonoFrame<intensity_t>() {
		delete mem;
	}
};
