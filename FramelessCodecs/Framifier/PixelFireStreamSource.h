#pragma once

#include "CameraEmulator/Source.h"
#include "CameraEmulator/PixelFire.h"

#include <fstream>
using std::istream;


class PixelFireStreamSource final : public Source<PixelFire> {
private:
	/*
	** Delegates to stream object.
	*/
	istream& stream;

public:
	/*
	** Constructor.
	*/
	PixelFireStreamSource(istream&);

	/*
	** Reads the next PixelFire object from the internal istream.
	*/
	void read(PixelFire&) final;
};
