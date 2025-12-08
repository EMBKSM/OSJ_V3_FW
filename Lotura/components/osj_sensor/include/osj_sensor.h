#ifndef OSJ_SENSOR_H
#define OSJ_SENSOR_H

#include <stdint.h>

void osj_sensor_init(void);
float osj_sensor_get_rms(int channel);
uint32_t osj_sensor_get_flow(int channel);
int osj_sensor_get_drain(int channel);

#endif