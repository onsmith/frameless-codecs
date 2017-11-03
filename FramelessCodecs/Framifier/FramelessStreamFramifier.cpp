#include "FramelessStreamFramifier.h"


int FramelessStreamFramifier::width() const {
	return frame.width();
}

int FramelessStreamFramifier::height() const {
	return frame.height();
}

size_t FramelessStreamFramifier::numPixels() const {
	return width() * height();
}

size_t FramelessStreamFramifier::index(const PixelFire &pixel) const {
	return pixel.y * width() + pixel.x;
}

double FramelessStreamFramifier::computeIntensity(const PixelFire &pixel) {
	return static_cast<double>(0x1 << pixel.d) / static_cast<double>(pixel.dt);
}

FramelessStreamFramifier::FramelessStreamFramifier(istream &input, ostream &output, int width, int height, int fps) :
	input(input),
	output(output),
	lastFireTimes(width * height),
	frame(width, height),
	fps(fps),
	tpf(tps / fps) {
	this->input.read(pixel);
}

void FramelessStreamFramifier::framifyPixelFires() {
	timestamp_t time_frame_end = t + tpf;

	timestamp_t next_fire_time = lastFireTimes[index(pixel)] + pixel.dt;
	while (next_fire_time < time_frame_end) {
		frame(pixel.x, pixel.y) = computeIntensity(pixel);
		lastFireTimes[index(pixel)] = next_fire_time;
		input.read(pixel);
		next_fire_time = lastFireTimes[index(pixel)] + pixel.dt;
	}

	output.write(frame);
	t = time_frame_end;
}
