#include "PixelFire.h"


PixelFire::PixelFire(index_t i, decimation_t d, timedelta_t dt) :
	i(i),
	d(d),
	dt(dt) {
}

void PixelFire::writeTextTo(ostream &output) const {
	output
		<< "("
		<< static_cast<int>(i) << ", "
		<< static_cast<int>(d) << ", "
		<< static_cast<int>(dt)
		<< ")" << std::endl;
}

void PixelFire::writeBinaryTo(ostream &output) const {
	output.write(reinterpret_cast<const char*>(&i),  sizeof(i));
	output.write(reinterpret_cast<const char*>(&d),  sizeof(d));
	output.write(reinterpret_cast<const char*>(&dt), sizeof(dt));
}

void PixelFire::readFrom(istream &input) {
	input.read(reinterpret_cast<char*>(&i),  sizeof(i));
	input.read(reinterpret_cast<char*>(&d),  sizeof(d));
	input.read(reinterpret_cast<char*>(&dt), sizeof(dt));
}
