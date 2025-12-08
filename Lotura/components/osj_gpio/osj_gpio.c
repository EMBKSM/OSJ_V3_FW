#include "osj_gpio.h"
#include "driver/gpio.h"
#include "gpio_definitions.h"


void osj_gpio_init(void) {
	// Basic Initialization using Fast Macros
	FAST_GPIO_OUTPUT_EN(PIN_STATUS_LED);
	FAST_GPIO_OUTPUT_EN(PIN_CH1_LED);
	FAST_GPIO_OUTPUT_EN(PIN_CH2_LED);

	// Inputs (Sensors & Switches)
	FAST_GPIO_INPUT_EN(PIN_DEBUG_MODE);
	FAST_GPIO_INPUT_EN(PIN_CH1_MODE);
	FAST_GPIO_INPUT_EN(PIN_CH2_MODE);

	// Note: Interrupts need standard driver configuration
}