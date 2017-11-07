#pragma once

#include <cstdint>

/*
** Represents the index of a pixel within a frame. Needs 23 bits to address
**   pixels in a 4k frame.
*/
typedef uint32_t index_t;

/*
** Represents an x or y coordinate of a pixel within a frame. Needs 12 bits per
**   coordinate to address pixels in a 4k frame.
*/
typedef uint16_t coordinate_t;

/*
** Represents a decimation value.
*/
typedef uint8_t decimation_t;

/*
** Represents a timestamp (number of ticks).
*/
typedef uint64_t timestamp_t;

/*
** Represents a difference of timestamps (number of ticks).
*/
typedef uint64_t timedelta_t;

/*
** Represents an amount of light.
*/
typedef double light_t;
