#include "TargetDController.h"

#include <cmath>


TargetDController::TargetDController(decimation_t init_d, timedelta_t target_dt) :
	init_d(init_d),
	target_dt(target_dt) {
}

decimation_t TargetDController::initD(index_t i) {
	return init_d;
}

/*inline static int log2(unsigned int index) {
	int targetlevel = 0;
	while (index >>= 1) { targetlevel++; }
	return targetlevel;
}*/

decimation_t TargetDController::nextD(index_t i, decimation_t last_d, timedelta_t last_dt) {
	int new_d = round(log2(static_cast<double>(target_dt) / last_dt) + last_d);
	if (new_d > MAX_D) { new_d = MAX_D; }
	else if (new_d < MIN_D) { new_d = MIN_D; }
	return new_d;
}
