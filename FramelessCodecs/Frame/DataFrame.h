#pragma once

#include "Frame.h"

#include <vector>
using std::vector;

#include <fstream>
using std::istream;
using std::ostream;


/**
 * DataFrame is an abstract implementation of the Frame class. The DataFrame
 *   class implements storage of frame intensity values by delegating to an
 *   internally-managed vector<T> instance. A DataFrame specifies the data type
 *   and number of intensity values, but allows subclasses to define the
 *   intensity addressing scheme.
 */
template <typename intensity_t>
class DataFrame : public Frame {
private:
	/*
	** Stores the frame data.
	*/
	vector<intensity_t> data_;


protected:
	/*
	** Constructor.
	*/
	DataFrame(int width, int height, int size) :
		Frame(width, height),
		data_(size) {
	}

	/*
	** Changes the dimensions of the frame.
	*/
	void resize(int width, int height, int size) {
		Frame::resize(width, height);
		data_.resize(size);
	}


public:
	/*
	** Gets the number of intensities stored by the frame.
	*/
	int size() const final {
		return data_.size();
	}

	/*
	** Gets a pointer to the underlying data managed by the frame object.
	*/
	intensity_t* data() const {
		return data_.data();
	}

	/*
	** Populates the frame's intensity data by reading from a given istream.
	**   Returns true if successful.
	*/
	bool readFrom(istream& stream) final {
		size_t const numBytes = size() * sizeof(intensity_t);
		stream.read(reinterpret_cast<char*>(data()), numBytes);
		return (stream.gcount() == numBytes);
	}

	/*
	** Writes the frame's intensity data to a given ostream.
	*/
	void writeTo(ostream& stream) final {
		size_t const numBytes = size() * sizeof(intensity_t);
		stream.write(reinterpret_cast<char*>(data()), numBytes);
	}
};
