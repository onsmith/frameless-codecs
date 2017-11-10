#include "VideoLightSource.h"


VideoLightSource::VideoLightSource(
	istream &stream,
	pixel_t width,
	pixel_t height,
	time_t framesPerSecond,
	time_t ticksPerFrame
) :
	LightSource(framesPerSecond, ticksPerFrame),
	stream(stream),
	frame(width, height) {
}

void VideoLightSource::nextFrame() {
	frame.readFrom(stream);
	for (int i = 0; i < numPixels(); i++) {
		frame(i) = scaleIntensity(frame(i));
		frame(i) /= ticksPerSecond();
	}
}

LightSource::light_t VideoLightSource::scaleIntensity(light_t intensity) {
	intensity *= 16384;
	intensity += 1;
	return intensity;
}

LightSource::time_t VideoLightSource::timeToAccumulateLight(pixel_t pixel, light_t quota, time_t offset) {
	return ceil(quota / frame(pixel));
}

LightSource::light_t VideoLightSource::accumulateLight(pixel_t pixel, time_t offset, time_t duration) {
	return duration * frame(pixel);
}

LightSource::pixel_t VideoLightSource::width() const {
	return frame.width();
}

LightSource::pixel_t VideoLightSource::height() const {
	return frame.height();
}

LightSource::pixel_t VideoLightSource::numPixels() const {
	return frame.width() * frame.height();
}
