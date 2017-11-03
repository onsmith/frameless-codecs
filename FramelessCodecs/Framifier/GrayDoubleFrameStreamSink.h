#pragma once

#include "CameraEmulator/Sink.h"
#include "Frame/GrayDoubleFrame.h"

#include <fstream>
using std::ostream;


class GrayDoubleFrameStreamSink final : public Sink<GrayDoubleFrame> {
private:
	/*
	** Delegates to stream object.
	*/
	ostream& stream;


public:
	/*
	** Constructor.
	*/
	GrayDoubleFrameStreamSink(ostream&);

	/*
	** Writes a GrayDoubleFrame object to the ostream.
	*/
	void write(GrayDoubleFrame&) final;
};
