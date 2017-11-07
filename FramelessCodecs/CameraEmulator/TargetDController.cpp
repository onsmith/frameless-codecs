#include "TargetDController.h"


TargetDController::TargetDController(decimation_t init_d, timedelta_t target_dt) :
	init_d(init_d),
	target_dt(target_dt) {
}

decimation_t TargetDController::initD(index_t i) {
	return init_d;
}

decimation_t TargetDController::nextD(index_t i, decimation_t last_d, timedelta_t last_dt) {
	if (last_dt < target_dt) {
		return (last_d < MAX_D) ? last_d + 1 : MAX_D;
	} else {
		return (last_d > MIN_D) ? last_d - 1 : MIN_D;
	}
}
