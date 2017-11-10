#include "LightSource.h"


LightSource::LightSource(time_t fps, time_t tpf) :
	fps(fps),
	tpf(tpf) {
}

LightSource::time_t LightSource::framesPerSecond() const {
	return fps;
}

LightSource::time_t LightSource::ticksPerFrame() const {
	return tpf;
}

LightSource::time_t LightSource::ticksPerSecond() const {
	return tpf * fps;
}
