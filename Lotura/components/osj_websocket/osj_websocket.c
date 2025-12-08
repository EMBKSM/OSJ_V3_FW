#include "osj_websocket.h"
#include "esp_log.h"
#include "esp_websocket_client.h"

static const char *TAG = "OSJ_WS";

void osj_websocket_start(void) {
	ESP_LOGI(TAG, "Starting WebSocket Client...");
}

void osj_websocket_send_status(int channel, int status) {
	// Construct JSON and send
}