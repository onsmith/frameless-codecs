#pragma once

#include <cstdint>

#include <fstream>
using std::istream;
using std::ostream;


struct PixelFire {
public:
	/*
	** Data types.
	*/
	typedef uint32_t index_t;
	typedef uint8_t  decimation_t;
	typedef uint16_t timedelta_t;

	/*
	** Data container fields.
	*/
	index_t      i;
	decimation_t d;
	timedelta_t  dt;

	/*
	** Constructors.
	*/
	PixelFire() = default;
	PixelFire(index_t, decimation_t, timedelta_t);

	/*
	** Writes a PixelFire as text to a given output stream.
	*/
	void writeTextTo(ostream&) const;

	/*
	** Writes a PixelFire as binary to a given output stream.
	*/
	void writeBinaryTo(ostream&) const;

	/*
	** Reads a PixelFire from a given input stream.
	*/
	void readFrom(istream&);
};
