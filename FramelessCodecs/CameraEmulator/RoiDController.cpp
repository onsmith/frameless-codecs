#include "RoiDController.h"


RoiDController::RoiDController(
	decimation_t roi_init_d,
	timedelta_t roi_target_dt,
	decimation_t bg_init_d,
	timedelta_t bg_target_dt,
	index_t stride,
	index_t x_min,
	index_t y_min,
	index_t x_max,
	index_t y_max
) :
	roi(roi_init_d, roi_target_dt),
	bg(bg_init_d, bg_target_dt),
	stride(stride),
	x_min(x_min),
	y_min(y_min),
	x_max(x_max),
	y_max(y_max) {
}

decimation_t RoiDController::initD(index_t i) {
	return isInRoi(i) ? roi.initD(i) : bg.initD(i);
}

decimation_t RoiDController::nextD(index_t i, decimation_t d, timedelta_t dt) {
	return isInRoi(i) ? roi.nextD(i, d, dt) : bg.nextD(i, d, dt);
}

bool RoiDController::isInRoi(index_t i) const {
	index_t x = this->x(i), y = this->y(i);
	return (x_min <= x && x <= x_max && y_min <= y && y <= y_max);
}

index_t RoiDController::x(index_t i) const {
	return i % stride;
}

index_t RoiDController::y(index_t i) const {
	return i / stride;
}
