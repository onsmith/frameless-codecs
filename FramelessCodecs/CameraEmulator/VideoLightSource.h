#pragma once

#include <fstream>
using std::istream;
using std::ostream;

#include "LightSource.h"

#include "Frame/GrayDoubleFrame.h"


class VideoLightSource final : public LightSource {
private:
	/*
	** Input stream for reading intensities as double values.
	*/
	istream& stream;

	/*
	** Buffers frames of intensity data from the input stream.
	*/
	GrayDoubleFrame frame;

	/*
	** Scales an intensity value.
	*/
	inline light_t scaleIntensity(light_t);


public:
	/*
	** Constructor.
	*/
	VideoLightSource(
		istream& stream,
		pixel_t width,
		pixel_t height,
		time_t framesPerSecond,
		time_t ticksPerFrame
	);

	/*
	** Moves to the next light source frame.
	*/
	void nextFrame() final;

	/*
	** Calculates amount of time required to accumulate a certain amount of
	**   light.
	*/
	time_t timeToAccumulateLight(pixel_t pixel, light_t amount, time_t offset) final;

	/*
	** Accumulates light over a predefined time interval.
	*/
	light_t accumulateLight(pixel_t pixel, time_t offset, time_t duration) final;

	/*
	** Gets the width of the scene in number of pixels.
	*/
	inline pixel_t width() const final;

	/*
	** Gets the height of the scene in number of pixels.
	*/
	inline pixel_t height() const final;

	/*
	** Gets the number pixels in the scene.
	*/
	inline pixel_t numPixels() const final;
};
