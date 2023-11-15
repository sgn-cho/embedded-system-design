#include <stdio.h>
#include <esp_log.h>
#include <esp_chip_info.h>
#include <esp_system.h>
#include <esp_flash.h>
#include <nvs_flash.h>
#include <esp_netif.h>
#include <esp_event.h>

#include "wifi/include/init.h"
#include "mqtt5/include/control.h"
#include "sys/include/sensord.h"
#include "./test_wifi.h"
#include <test_mqtt5.h>
#include "csi/include/init.h"

static const char *TAG = "main";

void __test_wifi_csi(void) {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
        ret == ESP_ERR_NVS_NEW_VERSION_FOUND
    ) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ESP_ERROR_CHECK(nvs_flash_init());    
    }
   
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    init_wifi();
    ESP_LOGI(TAG, "wifi initialized");

    ret = wifi_csi_init();
}

void app_main(void) {
    ESP_LOGI(TAG, "program started");
    test_mqtt5();

#if CONFIG_TEST_WIFI_AP
    test_ap();
#endif

#if CONFIG_TEST_MQTT5
    test_mqtt5();
#endif

    while (true) {
        vTaskDelay(pdTICKS_TO_MS(1000));
    }
}