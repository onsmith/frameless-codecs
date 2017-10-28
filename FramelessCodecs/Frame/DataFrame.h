#pragma once

#include "Frame.h"

#include <vector>
using std::vector;

#include <fstream>
using std::istream;
using std::ostream;


/**
 * A DataFrame is an abstract class that represents a single video frame that
 *   holds intensity data. A DataFrame object knows the data type of intensity
 *   values but not the organization of the intensities, which are specified
 *   by the concrete subclasses of this class.
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
	int size() const {
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


	/*
	** Exposes access to individual intensities in the frame. The meaning of the
	**   addressing parameters is defined by the derived classes.
	*/
	virtual intensity_t& intensityAt(int)           const = 0;
	virtual intensity_t& intensityAt(int, int)      const = 0;
	virtual intensity_t& intensityAt(int, int, int) const = 0;
};
