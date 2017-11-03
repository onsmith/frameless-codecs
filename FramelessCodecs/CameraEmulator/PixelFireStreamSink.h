#pragma once

#include "Sink.h"
#include "PixelFire.h"

#include <fstream>
using std::ostream;


class PixelFireStreamSink final : public Sink<PixelFire> {
private:
	/*
	** Delegates to stream object.
	*/
	ostream& stream;


public:
	/*
	** Constructor.
	*/
	PixelFireStreamSink(ostream&);

	/*
	** Writes a PixelFire object to the ostream.
	*/
	void write(const PixelFire&) final;
};
