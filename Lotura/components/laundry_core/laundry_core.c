#include "laundry_core.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "osj_sensor.h"
#include "osj_websocket.h"

void laundry_core_task(void *pvParameters) {
	// Main state machine loop
	while (1) {
		// 1. Read Sensors
		// 2. Logic Judgment (Wash/Dry)
		// 3. Send WebSocket update if needed
		vTaskDelay(pdMS_TO_TICKS(500)); // 500ms cycle
	}
}