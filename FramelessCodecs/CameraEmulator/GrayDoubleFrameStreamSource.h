#pragma once

#include "Source.h"

#include "Frame/GrayDoubleFrame.h"

#include <fstream>
using std::istream;


class GrayDoubleFrameStreamSource final : public Source<GrayDoubleFrame> {
private:
	/*
	** Delegates to stream object.
	*/
	istream& stream;

public:
	/*
	** Constructor.
	*/
	GrayDoubleFrameStreamSource(istream&);

	/*
	** Reads the next GrayDoubleFrame object from the internal istream.
	*/
	void read(GrayDoubleFrame&) final;
};
