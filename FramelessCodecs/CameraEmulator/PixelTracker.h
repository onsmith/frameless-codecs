#pragma once


struct PixelTracker {
public:
	/*
	** The pixel's coordinates in the 2D frame.
	*/
	int x, y;

	/*
	** The pixel's current decimation value.
	*/
	unsigned int d;

	/*
	** The timestamp when the pixel was last fired.
	*/
	unsigned long int t;

	/*
	** The amount of light accumulated by the pixel.
	*/
	double accumulated_light;

	/*
	** The amount of light that must be accumulated before the pixel fires.
	*/
	double target_light;
};

