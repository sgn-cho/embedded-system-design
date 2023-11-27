#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>
#include <esp_wifi.h>
#include <esp_event.h>
#include <esp_log.h>

#include "include/handler.h"

static const char *TAG = "wi-fi/init";
static EventGroupHandle_t wifi_event_group;

#ifndef WIFI_CONNECTED_BIT
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1
#endif

static wifi_config_t wifi_cfg = {
    .sta = {
        .ssid = CONFIG_WIFI_SSID,
        .password = CONFIG_WIFI_PASSWORD,
        .threshold.authmode = WIFI_AUTH_WPA2_PSK,
    }
};

/* function prototypes */


esp_err_t init_wifi(void) {
    esp_err_t ret;

    esp_netif_create_default_wifi_sta();
    wifi_event_group = xEventGroupCreate();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ret = esp_wifi_init(&cfg);
    ESP_RETURN_ON_ERROR(ret, TAG, "esp_wifi_init failed");

    esp_event_handler_instance_t instance_any_id;
    ret = __register_instance_any_id(&instance_any_id);
    ESP_RETURN_ON_ERROR(ret, TAG, "__register_instance_any_id failed");

    esp_event_handler_instance_t instance_any_ip;
    ret = __register_instance_any_ip(&instance_any_ip);
    ESP_RETURN_ON_ERROR(ret, TAG, "__register_instance_any_ip failed");

    ret = esp_wifi_set_mode(WIFI_MODE_STA);
    ESP_RETURN_ON_ERROR(ret, TAG, "esp_wifi_set_mode failed");

    ret = esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_cfg);
    ESP_RETURN_ON_ERROR(ret, TAG, "esp_wifi_set_config failed");

    ret = esp_wifi_start();
    ESP_RETURN_ON_ERROR(ret, TAG, "esp_wifi_start failed");

    EventBits_t bits = xEventGroupWaitBits(
        wifi_event_group,
        WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
        pdFALSE,
        pdFALSE,
        portMAX_DELAY
    );

    if (bits & WIFI_CONNECTED_BIT) {
        ESP_LOGI(TAG, "connected to AP");
    } else if (bits & WIFI_FAIL_BIT) {
        ESP_LOGI(TAG, "failed to connect to AP");
    } else {
        ESP_LOGE(TAG, "UNEXPECTED EVENT");
    }
}

static esp_err_t __register_instance_any_id(esp_event_handler_instance_t *ins) {
    return esp_event_handler_instance_register(
        WIFI_EVENT,
        ESP_EVENT_ANY_ID,
        &__wifi_event_handler,
        NULL,
        ins
    );
}

static esp_err_t __register_instance_any_ip(esp_event_handler_instance_t *ins) {
    return esp_event_handler_instance_register(
        IP_EVENT,
        ESP_EVENT_ANY_ID,
        &__ip_event_handler,
        NULL,
        ins
    );
}