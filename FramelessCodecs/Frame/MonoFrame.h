#pragma once

#include <vector>
using std::vector;

#include <fstream>
using std::istream;
using std::ostream;


template <typename intensity_t>
class MonoFrame {
private:
	/*
	** Stores the width and height of the frame.
	*/
	int width_, height_;


	/*
	** Stores the frame data.
	*/
	vector<intensity_t> data_;


public:
	/*
	** Constructor.
	*/
	MonoFrame(int width, int height) :
		width_(width),
		height_(height),
		data_(width * height) {
	}


	/*
	** Gets the width of the frame.
	*/
	int width() const {
		return width_;
	}


	/*
	** Gets the height of the frame.
	*/
	int height() const {
		return height_;
	}


	/*
	** Gets the number of intensities stored by the frame.
	*/
	int size() const {
		return data_.size();
	}


	/*
	** Gets a pointer to the underlying data managed by the frame object.
	*/
	intensity_t* data() {
		return data_.data();
	}


	/*
	** Gets a reference to a given pixel's intensity value.
	*/
	intensity_t& intensityAt(int i) {
		return data()[i];
	}


	/*
	** Gets a reference to a given pixel's intensity value.
	*/
	intensity_t& intensityAt(int x, int y) {
		return intensityAt(y * width() + x);
	}


	/*
	** Changes the dimensions of the frame.
	*/
	void setDimensionsTo(int width, int height) {
		width_  = width;
		height_ = height;
		data_.resize(width * height);
	}


	/*
	** Populates the frame's intensity data by reading from a given istream.
	**   Returns true if successful.
	*/
	bool readFrom(istream& stream) {
		size_t const numBytes = size() * sizeof(intensity_t);
		stream.read(reinterpret_cast<char*>(data()), numBytes);
		return (stream.gcount() == numBytes);
	}


	/*
	** Writes the frame's intensity data to a given ostream.
	*/
	void writeTo(ostream& stream) {
		size_t const numBytes = size() * sizeof(intensity_t);
		stream.write(reinterpret_cast<char*>(data()), numBytes);
	}
};
