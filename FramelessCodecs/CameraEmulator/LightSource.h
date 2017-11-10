#pragma once

#include <cstdint>


class LightSource {
public:
	/*
	** Declare data types.
	*/
	typedef uint32_t pixel_t;
	typedef uint64_t time_t;
	typedef double light_t;


private:
	/*
	** Frames per second, determined by aspects of the light source model.
	*/
	const time_t fps;

	/*
	** Ticks per frame, determined by aspects of the camera emulator.
	*/
	const time_t tpf;


public:
	/*
	** Constructor.
	*/
	LightSource(time_t fps, time_t tpf);

	/*
	** Gets the number of frames per second.
	*/
	time_t framesPerSecond() const;

	/*
	** Gets the number of ticks per frame.
	*/
	time_t ticksPerFrame() const;

	/*
	** Gets the number of ticks per second.
	*/
	time_t ticksPerSecond() const;

	/*
	** Gets the width of the scene in number of pixels.
	*/
	virtual pixel_t width() const = 0;

	/*
	** Gets the height of the scene in number of pixels.
	*/
	virtual pixel_t height() const = 0;

	/*
	** Gets the number pixels in the scene.
	*/
	virtual pixel_t numPixels() const = 0;

	/*
	** Moves to the next light source frame.
	*/
	virtual void nextFrame() = 0;

	/*
	** Calculates amount of time required to accumulate a certain amount of
	**   light.
	*/
	virtual time_t timeToAccumulateLight(pixel_t pixel, light_t amount, time_t offset) = 0;

	/*
	** Calculates amount of light accumulated over a predefined time interval.
	*/
	virtual light_t accumulateLight(pixel_t pixel, time_t offset, time_t duration) = 0;

	/*
	** Base classes should have virtual destructors.
	*/
	virtual ~LightSource() = default;
};
