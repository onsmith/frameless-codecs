#pragma once


#include <cassert>

#include <fstream>
using std::istream;
using std::ostream;


template <typename intensity_t>
class Plane {
private:
	/*
	 ** The width and height of the plane, in pixels.
	 */
	int w, h;


	/*
	 ** A pointer to the memory holding the plane data. Note that the memory must
	 **   be externally managed, and this is not an owning pointer.
	 */
	intensity_t* mem;


public:
	/*
	** Gets the width of the plane, in pixels.
	*/
	int width() const {
		return w;
	}


	/*
	** Gets the height of the plane, in pixels.
	*/
	int height() const {
		return h;
	}


	/*
	** Gets the total number of pixels in the plane.
	*/
	int numPixels() const {
		return w * h;
	}


private:
	/*
	** Gets the size of the pixel intensity array, in number of bytes.
	*/
	size_t sizeofData() const {
		return numPixels() * sizeof(intensity_t);
	}


public:
	/*
	** Gets the underlying array of pixel intensity values.
	*/
	intensity_t* data() const {
		return mem;
	}


	/*
	** Gets the intensity of the pixel located at position i, where pixels are
	**   zero-indexed in row-major order starting from the top left of the plane.
	*/
	intensity_t& intensityAt(int i) const {
		return mem[i];
	}


	/*
	** Gets the intensity of the pixel located at position (x, y), where the
	**   origin is located at the top left corner of the plane, and pixels are
	**   zero-indexed.
	*/
	intensity_t& intensityAt(int x, int y) const {
		return mem[y * w + x];
	}


	/*
	** Populates the plane's intensity array by reading from a given istream.
	**   Returns true if successful.
	*/
	bool readFrom(istream& stream) {
		stream.read(reinterpret_cast<char*>(mem), sizeofData());
		return (stream.gcount() == sizeofData());
	}


	/*
	** Writes the plane's intensity array to a given ostream.
	*/
	void writeTo(ostream& stream) {
		stream.write(reinterpret_cast<char*>(mem), sizeofData());
	}


	/*
	** Sets the plane's internal pointer, which should point to to the memory
	**   storing the pixel intensity array.
	*/
	void pointTo(intensity_t* mem) {
		this->mem = mem;
	}


	/*
	** Changes the plane's dimensions.
	*/
	void setDimensionsTo(int width, int height) {
		assert(width  > 0);
		assert(height > 0);
		this->width  = width;
		this->height = height;
	}


	/*
	** Constructor.
	*/
	Plane(int width, int height, intensity_t* mem = nullptr) :
		w(width),
		h(height),
		mem(mem) {
		assert(width  > 0);
		assert(height > 0);
	}
};
