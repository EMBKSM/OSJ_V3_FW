#include "osj_nvs.h"
#include "nvs.h"
#include "nvs_flash.h"

void osj_nvs_init(void) {
	// Initialize NVS partition
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
		ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);
}

void osj_nvs_set_str(const char *key, const char *value) {
	// NVS set logic
}

void osj_nvs_get_str(const char *key, char *out_value, size_t max_len) {
	// NVS get logic
}