#pragma once


#include "Plane.h"

#include <algorithm>
using std::copy;


template <typename intensity_t>
class ColorFrame {
protected:
	/*
	** A ColorFrame encapsulates three Plane objects.
	*/
	Plane<intensity_t> plane[3];


private:
	/*
	 ** This object manages its own memory.
	 */
	intensity_t* mem;


	/*
	** Sets the three internal plane objects to point to the correct locations in
	**   memory.
	*/
	void setPlanePointers() const {
		plane[0].pointTo(mem);
		plane[1].pointTo(mem + plane[0].numPixels());
		plane[2].pointTo(mem + plane[0].numPixels() + plane[1].numPixels());
	}


public:
	/*
	** Gets the width of the frame, in pixels.
	*/
	int width() const {
		return plane[0].width();
	}


	/*
	** Gets the height of the frame, in pixels.
	*/
	int height() const {
		return plane[0].height();
	}


	/*
	** Gets the total number of pixels in the frame.
	*/
	int numPixels() const {
		return plane[0].numPixels();
	}


	/*
	** Calculates the total number of intensity values stored in the frame.
	*/
	int size() const {
		return
			plane[0].size() +
			plane[1].size() +
			plane[2].size();
	}


	/*
	** Gets the underlying array of pixel intensity values.
	*/
	intensity_t* data() const {
		return mem;
	}


	/*
	** Populates the frame's intensity array by reading from a given istream.
	**   Returns true if successful.
	*/
	bool readFrom(istream& stream) {
		return plane[0].readFrom(stream);
		return plane[1].readFrom(stream);
		return plane[2].readFrom(stream);
	}


	/*
	** Writes the frame's intensity array to a given ostream.
	*/
	void writeTo(ostream& stream) {
		return plane[0].writeTo(stream);
		return plane[1].writeTo(stream);
		return plane[2].writeTo(stream);
	}


	/*
	** Constructors.
	*/
	ColorFrame(int width, int height) :
		plane{{width, height}, {width, height}, {width, height}},
		mem(new intensity_t[width * height * 3]) {
		setPlanePointers();
	}

	ColorFrame(int width1, int height1, int width2, int height2) :
		plane{{width1, height1}, {width2, height2}, {width2, height2}},
		mem(new intensity_t[width1 * height1 + width2 * height2 * 2]) {
		setPlanePointers();
	}

	ColorFrame(int width1, int height1, int width2, int height2, int width3, int height3) :
		plane{{width1, height1}, {width2, height2}, {width3, height3}},
		mem(new intensity_t[width1 * height1 + width2 * height2 + width3 * height3]) {
		setPlanePointers();
	}


	/*
	** Copy constructor.
	*/
	ColorFrame(const ColorFrame<intensity_t>& obj) :
		plane{obj.plane[0], obj.plane[1], obj.plane[2]},
		mem(new intensity_t[obj.size()]) {
		copy(obj.mem, obj.mem + obj.size(), mem);
		setPlanePointers();
	}


	/*
	** Copy assignment operator.
	*/
	ColorFrame& operator=(const ColorFrame<intensity_t>& obj) {
		if (this != &obj) {
			if (size() != obj.size()) {
				delete mem;
				mem = new intensity_t[obj.size()];
			}
			plane[0] = obj.plane[0];
			plane[1] = obj.plane[1];
			plane[2] = obj.plane[2];
			setPlanePointers();
			copy(obj.mem, obj.mem + obj.size(), mem);
		}
		return *this;
	}


	/*
	** Destructor.
	*/
	~ColorFrame<intensity_t>() {
		delete mem;
	}
};
