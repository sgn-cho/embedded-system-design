#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

const char *TAG = "main";

void __initialize_prequisites(void) {
    esp_err_t nvs_ret = nvs_flash_init();
    if (nvs_ret == ESP_ERR_NVS_NO_FREE_PAGES ||
        nvs_ret == ESP_ERR_NVS_NEW_VERSION_FOUND
    ) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ESP_ERROR_CHECK(nvs_flash_init());    
    }
   
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_LOGI(TAG, "netif initialized");

    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_LOGI(TAG, "event loop created");

    // wifi_init_sta();
    // ESP_LOGI(TAG, "wifi initialized");

    ESP_LOGI(TAG, "prequisites initialized");
    return;
}

void app_main(void) {
    ESP_LOGI(TAG, "program started");
    __initialize_prequisites();
}