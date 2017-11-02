#include "PixelFireConsoleSink.h"

#include <iostream>
using std::cout;
using std::endl;


void PixelFireConsoleSink::write(PixelFire &pf) {
	cout
		<< "("
		<< pf.x << ", "
		<< pf.y << ", "
		<< pf.d << ", "
		<< pf.dt
		<< ")" << endl;
}
