#include "ConstDController.h"


ConstDController::ConstDController(decimation_t d) :
	d(d) {
}

decimation_t ConstDController::initD(int x, int y) {
	return d;
}

decimation_t ConstDController::nextD(int x, int y, decimation_t last_d, timedelta_t last_dt) {
	return d;
}
