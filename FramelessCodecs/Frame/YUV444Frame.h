#pragma once

#include <vector>
using std::vector;

#include <fstream>
using std::istream;
using std::ostream;


template <typename intensity_t>
class YUV444Frame {
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
	YUV444Frame(int width, int height) :
		width_(width),
		height_(height),
		data_(width * height * 3) {
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
	** Gets a pointer to the underlying data managed by the frame.
	*/
	intensity_t* data() const {
		return data_.data();
	}


	/*
	** Gets a pointer to the underlying y plane memory.
	*/
	intensity_t* y() const {
		return data();
	}


	/*
	** Gets a pointer to the underlying u plane memory.
	*/
	intensity_t* u() const {
		return y() + width() * height();
	}


	/*
	** Gets a pointer to the underlying v plane memory.
	*/
	intensity_t* v() const {
		return u() + width() * height();
	}


	/*
	** Gets a reference to a given pixel's y-plane intensity value.
	*/
	intensity_t& y(int i) const {
		return y()[i];
	}


	/*
	** Gets a reference to a given pixel's u-plane intensity value.
	*/
	intensity_t& u(int i) const {
		return u()[i];
	}


	/*
	** Gets a reference to a given pixel's v-plane intensity value.
	*/
	intensity_t& v(int i) const {
		return v()[i];
	}


	/*
	** Gets a reference to a given pixel's y-plane intensity value.
	*/
	intensity_t& y(int x, int y) const {
		return this->y(y * width() + x);
	}


	/*
	** Gets a reference to a given pixel's u-plane intensity value.
	*/
	intensity_t& u(int x, int y) const {
		return u(y * width() + x);
	}


	/*
	** Gets a reference to a given pixel's v-plane intensity value.
	*/
	intensity_t& v(int x, int y) const {
		return v(y * width() + x);
	}


	/*
	** Changes the dimensions of the frame.
	*/
	void setDimensionsTo(int width, int height) {
		width_  = width;
		height_ = height;
		data_.resize(width * height * 3);
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
