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

static const char *TAG = "main";

void app_main(void) {
    ESP_LOGI(TAG, "program started");

#if CONFIG_TEST_WIFI_AP
    test_ap();
#endif

    while (true) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}