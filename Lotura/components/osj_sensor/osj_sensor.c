#include "osj_sensor.h"
#include "gpio_definitions.h"

void osj_sensor_init(void) {
	// ADC & PCNT Initialization code will go here
}

float osj_sensor_get_rms(int channel) {
	// Implementation for CT Sensor RMS calculation
	return 0.0f;
}

uint32_t osj_sensor_get_flow(int channel) {
	// Implementation for Flow Sensor calculation
	return 0;
}

int osj_sensor_get_drain(int channel) {
	// Implementation for Drain Sensor check
	if (channel == 1)
		return FAST_GPIO_READ(PIN_DRAIN_SENSOR_1);
	else
		return FAST_GPIO_READ(PIN_DRAIN_SENSOR_2);
}