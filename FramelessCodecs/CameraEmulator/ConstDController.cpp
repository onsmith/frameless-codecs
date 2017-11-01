#include "ConstDController.h"


ConstDController::ConstDController(decimation_t d) :
	d(d) {
}

ConstDController::decimation_t ConstDController::init(int x, int y) {
	return d;
}

ConstDController::decimation_t ConstDController::next(int x, int y, ConstDController::timedelta_t last_dt) {
	return d;
}
