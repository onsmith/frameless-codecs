#pragma once

#include <cstdint>


struct PixelTracker {
public:
	/*
	** Data types.
	*/
	typedef uint64_t time_t;
	typedef uint32_t pixel_t;
	typedef double   light_t;
	typedef uint8_t  decimation_t;

	/*
	** The pixel's index in the 2D frame.
	*/
	pixel_t i;

	/*
	** The pixel's current decimation value.
	*/
	decimation_t d;

	/*
	** The timestamp when the pixel was last fired.
	*/
	time_t last_fire_time;

	/*
	** The amount of light accumulated by the pixel.
	*/
	light_t accumulated_light;

	/*
	** The amount of light that must be accumulated before the pixel fires.
	*/
	light_t target_light;

	/*
	** Constructors.
	*/
	PixelTracker();
	PixelTracker(pixel_t);
	PixelTracker(pixel_t, decimation_t);

	/*
	** Calculates the amount of light needed before the pixel may fire.
	*/
	light_t lightDeficit() const;

	/*
	** Returns true if the pixel has accumulated enough light to fire.
	*/
	bool readyToFire() const;

	/*
	** Fires the pixel at a given time, discharging its accumulator and updating
	**   the time it was last fired.
	*/
	void fire(time_t);

	/*
	** Changes the pixel's decimation value.
	*/
	void updateDecimation(decimation_t);
};
