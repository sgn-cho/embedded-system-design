#include <mqtt_client.h>
#include <esp_log.h>
#include <esp_err.h>
#include <esp_check.h>
#include <esp_event.h>

#include "./include/handler.h"

static const char *TAG = "mqtt5-client/init";
esp_mqtt5_client_handle_t __mqtt5_client;

#ifndef CONFIG_BROKER_URL
#define CONFIG_BROKER_URL "mqtt://localhost"
#endif


/* function prototypes */
static esp_err_t __init_mqtt5(esp_mqtt_client_config_t *cfg);

esp_err_t init_mqtt5_client(void) {
    esp_mqtt_client_config_t cfg = {
        .broker.address.uri = CONFIG_BROKER_URL,
    };

    esp_err_t ret = __init_mqtt5(&cfg);
    return ret;
}

static esp_err_t __init_mqtt5(esp_mqtt_client_config_t *cfg) {
    esp_err_t ret;

    __mqtt5_client = esp_mqtt_client_init(cfg);
    if (__mqtt5_client == NULL) {
        ESP_LOGE(TAG, "Failed to initialize MQTT client");
        return ESP_FAIL;
    }

    ret = esp_mqtt_client_register_event(
        __mqtt5_client,
        MQTT_EVENT_CONNECTED,
        __mqtt5_sys_event_handler,
        NULL
    );
    ESP_RETURN_ON_ERROR(ret, TAG, "Failed to register mqtt event handler");

    ret = esp_mqtt_client_start(__mqtt5_client);
    ESP_RETURN_ON_ERROR(ret, TAG, "Failed to start mqtt client");

    return ret;
}