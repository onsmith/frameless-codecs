#include "TargetDController.h"


TargetDController::TargetDController(decimation_t init_d, timedelta_t target_dt) :
	init_d(init_d),
	target_dt(target_dt) {
}

decimation_t TargetDController::initD(index_t i) {
	return init_d;
}

inline static int log2(unsigned int index) {
	int targetlevel = 0;
	while (index >>= 1) { targetlevel++; }
	return targetlevel;
}

decimation_t TargetDController::nextD(index_t i, decimation_t last_d, timedelta_t last_dt) {
	int new_d = log2(target_dt) - log2(last_dt) + last_d;
	if (new_d > 15) { new_d = 15; }
	else if (new_d < 0) { new_d = 0; }
	return new_d;
}
