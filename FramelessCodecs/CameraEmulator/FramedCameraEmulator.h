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
	const long unsigned int fps;

	/*
	** Ticks per second.
	*/
	const long unsigned int tps;

	/*
	** Ticks per frame.
	*/
	const long unsigned int tpf;

	/*
	** Ticks per frame.
	*/
	DController &tpf;


public:
	/*
	** Constructor.
	*/
	FramedCameraEmulator(int width, int height, int fps, int tps);

	/*
	** Main method that runs the emulator.
	*/
	void emulate(istream& input, ostream& output) const;
};
