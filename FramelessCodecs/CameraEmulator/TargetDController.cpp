#include "TargetDController.h"


TargetDController::TargetDController(DController::decimation_t init_d, DController::timedelta_t target_dt) :
	init_d(init_d),
	target_dt(target_dt) {
}

DController::decimation_t TargetDController::initD(int x, int y) {
	return init_d;
}

DController::decimation_t TargetDController::nextD(int x, int y, DController::decimation_t last_d, DController::timedelta_t last_dt) {
	if (last_dt < target_dt) {
		return (last_d < MAX_D) ? last_d + 1 : MAX_D;
	} else {
		return (last_d > MIN_D) ? last_d - 1 : MIN_D;
	}
}
