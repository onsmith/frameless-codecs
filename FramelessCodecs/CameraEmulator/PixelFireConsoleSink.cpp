#include "PixelFireConsoleSink.h"

#include <iostream>
using std::cout;
using std::endl;


void PixelFireConsoleSink::write(PixelFire &pf) {
	cout
		<< "("
		<< static_cast<int>(pf.x) << ", "
		<< static_cast<int>(pf.y) << ", "
		<< static_cast<int>(pf.d) << ", "
		<< static_cast<int>(pf.dt)
		<< ")" << endl;
}
