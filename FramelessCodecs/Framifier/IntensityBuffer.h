#pragma once

#include "Intensity.h"

#include "CameraEmulator/DataTypes.h"
#include "CameraEmulator/PixelFire.h"

#include <fstream>
using std::istream;

#include <vector>
using std::vector;

#include <queue>
using std::queue;


class IntensityBuffer {
private:
	/*
	** Composed with a stream object.
	*/
	istream& stream;

	/*
	** Buffers PixelFire objects from the istream.
	*/
	vector<queue<Intensity>> buffer;


public:
	/*
	** Constructor.
	*/
	IntensityBuffer(istream&, size_t);

	/*
	** Ensures that a PixelFire object exists for a given pixel index, consuming
	**   and buffering as many PixelFire objects from the stream as necessary.
	*/
	void fillBuffer(index_t);

	/*
	** Returns a reference to the next PixelFire object for a given pixel index,
	**   if one exists.
	*/
	Intensity& next(index_t);

	/*
	** Removes the next PixelFire object for a given pixel index from the buffer,
	**   if it exists.
	*/
	void pop(index_t);

	/*
	** Checks if the buffer for a given pixel is empty.
	*/
	bool empty(index_t) const;
};
