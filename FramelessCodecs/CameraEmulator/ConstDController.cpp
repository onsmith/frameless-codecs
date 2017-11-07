#include "ConstDController.h"


ConstDController::ConstDController(decimation_t d) :
	d(d) {
}

decimation_t ConstDController::initD(index_t i) {
	return d;
}

decimation_t ConstDController::nextD(index_t i, decimation_t last_d, timedelta_t last_dt) {
	return d;
}
