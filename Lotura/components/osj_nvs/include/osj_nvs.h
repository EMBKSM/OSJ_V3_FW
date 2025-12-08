#ifndef OSJ_NVS_H
#define OSJ_NVS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


void osj_nvs_init(void);
void osj_nvs_set_str(const char *key, const char *value);
void osj_nvs_get_str(const char *key, char *out_value, size_t max_len);

#endif