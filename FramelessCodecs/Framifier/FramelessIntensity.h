#pragma once

#include <cstdint>


struct FramelessIntensity {
public:
	/*
	** Data types.
	*/
	typedef uint8_t  decimation_t;
	typedef uint16_t time_t;

	/*
	** Encapsulated data.
	*/
	decimation_t d;
	time_t       dt;

	/*
	** Constructors.
	*/
	FramelessIntensity() = default;
	FramelessIntensity(decimation_t, uint16_t);

	/*
	** Converts an FramelessIntensity to a double value between 0 and 1.
	*/
	double toDouble(uint64_t ticks_per_second) const;
	static double toDouble(decimation_t d, time_t dt, uint64_t ticks_per_second);
};
