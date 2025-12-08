#ifndef COMMON_DEFS_H
#define COMMON_DEFS_H

#include <stdbool.h>
#include <stdint.h>


typedef enum { MODE_WASHER = 0, MODE_DRYER = 1 } device_mode_t;

typedef enum {
	STATUS_IDLE = 0,
	STATUS_WORKING = 1,
	STATUS_ERROR = 2
} device_status_t;

#endif // COMMON_DEFS_H
