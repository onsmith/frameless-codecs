#pragma once

#include <fstream>
using std::istream;
using std::ostream;

#include "DController.h"


class FramedCameraEmulator {
private:
	/*
	** Frame width.
	*/
	const int width;

	/*
	** Frame height.
	*/
	const int height;

	/*
	** Frames per second.
	*/
	const long int fps;

	/*
	** Ticks per second.
	*/
	const long unsigned int tps;

	/*
	** Ticks per frame.
	*/
	const long int tpf;

	/*
	** Decimation controller.
	*/
	DController &dController;


public:
	/*
	** Constructor.
	*/
	FramedCameraEmulator(int width, int height, int fps, int tps);

	/*
	** Main method that runs the emulator; returns number of frames read.
	*/
	int emulate(istream& input, ostream& output) const;
};
