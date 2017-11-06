#pragma once

#include "Intensity.h"

#include "CameraEmulator/Source.h"
#include "CameraEmulator/DataTypes.h"
#include "CameraEmulator/PixelFire.h"

#include <fstream>
using std::istream;

#include <vector>
using std::vector;

#include <queue>
using std::queue;


class OrderedPixelFireStreamSource final : public Source<PixelFire> {
private:
	/*
	** Delegates to stream object.
	*/
	istream& stream;

	/*
	** Buffers PixelFire objects from the istream.
	*/
	vector<queue<Intensity>> buffer;

	/*
	** Stride of the frame.
	*/
	const int stride;

	/*
	** Convenience method to get a PixelFire object's index.
	*/
	inline int index(const PixelFire&) const;

	/*
	** For diagnostic purposes, keeps track of the size of the buffer.
	*/
	unsigned long int bufferSize;


public:
	/*
	** Constructor.
	*/
	OrderedPixelFireStreamSource(istream&, int, int);

	/*
	** Reads the next PixelFire object from the internal istream.
	*/
	void read(PixelFire&) final;

	/*
	** Ensures that a PixelFire object exists for a given pixel index, consuming
	**   and buffering as many PixelFire objects from the stream as necessary.
	*/
	void fillBuffer(int);

	/*
	** Returns a reference to the next PixelFire object for a given pixel index,
	**   if one exists.
	*/
	Intensity& next(int);

	/*
	** Removes the next PixelFire object for a given pixel index from the buffer,
	**   if it exists.
	*/
	void pop(int);

	/*
	** Checks if the buffer for a given pixel is empty.
	*/
	bool empty(int) const;

	/*
	** Gets the number of currently buffered intensity values.
	*/
	int size() const;
};
