#include <stdio.h>
#include <esp_err.h>
#include <esp_check.h>
#include <esp_log.h>
#include <nvs_flash.h>
#include <esp_netif.h>
#include <esp_event.h>

#include "initialize_camera.h"

static const char *TAG = "sys_init";

/* function prototypes */

static esp_err_t __init_prequisites(void);

/* end of function prototypes */

void init_sys(void) {
    esp_err_t ret = __init_prequisites();

    if (ret == ESP_OK) ESP_LOGI(TAG, "System initialized");
    else ESP_LOGE(TAG, "System initialization failed");
}

static esp_err_t __init_prequisites(void) {
    esp_err_t ret;

    ret = nvs_flash_init();

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
        ret == ESP_ERR_NVS_NEW_VERSION_FOUND
    ) {
            ESP_ERROR_CHECK(nvs_flash_erase());
            ESP_ERROR_CHECK(nvs_flash_init());
    }

    ret = esp_netif_init();
    ESP_RETURN_ON_ERROR(ret, TAG, "esp_netif_init() failed");

    ret = esp_event_loop_create_default();
    ESP_RETURN_ON_ERROR(ret, TAG, "esp_event_loop_create_default() failed");

    ret = init_camera();
    ESP_RETURN_ON_ERROR(ret, TAG, "init_camera() failed");

    return ret;
}