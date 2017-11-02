#include "ConstDController.h"


ConstDController::ConstDController(DController::decimation_t d) :
	d(d) {
}

DController::decimation_t ConstDController::initD(int x, int y) {
	return d;
}

DController::decimation_t ConstDController::nextD(int x, int y, DController::decimation_t last_d, DController::timedelta_t last_dt) {
	return d;
}
