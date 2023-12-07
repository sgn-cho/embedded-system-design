#include <stdio.h>
#include <esp_log.h>
#include <esp_chip_info.h>
#include <esp_system.h>
#include <esp_flash.h>
#include <nvs_flash.h>
#include <esp_netif.h>
#include <esp_event.h>

static const char *TAG = "sys";

/* function prototypes */

static void __init_prequisites(void);
static void __init_temperature_sensor(void);
static void __init_camera(void);
static void __init_soil_moisture_sensor(void);

/* end of fuction prototypes */


void sys_init_custom(void) {
    __init_prequisites();

    ESP_LOGD(TAG, "prequisites initialized");
    return;
}

static void __init_prequisites(void) {
    esp_err_t nvs_ret = nvs_flash_init();
    if (nvs_ret == ESP_ERR_NVS_NO_FREE_PAGES ||
        nvs_ret == ESP_ERR_NVS_NEW_VERSION_FOUND
    ) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ESP_ERROR_CHECK(nvs_flash_init());    
    }
   
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_LOGD(TAG, "netif initialized");

    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_LOGD(TAG, "event loop created");
}