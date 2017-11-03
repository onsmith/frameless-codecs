#pragma once

#include "CameraEmulator/Sink.h"
#include "CameraEmulator/PixelFire.h"
#include "Frame/GrayDoubleFrame.h"

#include <fstream>
using std::ostream;


class GrayDoubleFrameStreamSink final : public Sink<PixelFire> {
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
	** Writes a PixelFire object to the ostream.
	*/
	void write(const PixelFire&) final;
};
