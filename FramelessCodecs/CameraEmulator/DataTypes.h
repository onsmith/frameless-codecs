#pragma once

#include <cstdint>

/*
** Represents an x or y coordinate of a pixel within a frame. Needs 12 bits per
**   coordinate to store 4k addresses.
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
