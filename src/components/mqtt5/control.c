#include <mqtt_client.h>
#include <esp_log.h>
#include <esp_err.h>
#include <esp_check.h>
#include <event.h>

#ifndef BROKER_URL
#define BROKER_URL              CONFIG_BROKER_URL    
#endif

static const char *TAG = "mqtt5";
static esp_mqtt5_client_handle_t client;

/* function prototypes */

esp_err_t __init_mqtt5(esp_mqtt_client_config_t *cfg);

/* end of function prototypes */

void init_mqtt5(void) {
    esp_mqtt_client_config_t cfg = {
        .broker.address.uri = BROKER_URL,
    };

    __init_mqtt5(&cfg);
}

esp_err_t __init_mqtt5(esp_mqtt_client_config_t *cfg) {
    esp_err_t ret;
    
    client = esp_mqtt_client_init(cfg);
    if (client == NULL) {
        ESP_LOGE(TAG, "Failed to initialize mqtt client");
        return ESP_FAIL;
    }

    ret = esp_mqtt_client_register_event(
        client,
        MQTT_EVENT_CONNECTED,
        __mqtt5_sys_event_handler,
        NULL
    );
    ESP_RETURN_ON_ERROR(ret, TAG, "Failed to register mqtt event handler");

    ret = esp_mqtt_client_start(client);
    ESP_RETURN_ON_ERROR(ret, TAG, "Failed to start mqtt client");

    return ret;
}

esp_err_t publish_mqtt5_message(char *message, char *topic, int length, int qos) {
    int message_id = esp_mqtt_client_publish(client, topic, message, length, qos, 0);

    if (qos == 1 || qos == 2) {
        // TODO!
        return ESP_FAIL;
    }

    return ESP_OK;
}

esp_err_t subscribe_mqtt5_topic(
    char *topic,
    int qos,
    void (*handler)(void*, esp_event_base_t, int32_t, void*)
) {
    int ret = esp_mqtt_client_subscribe(client, topic, qos);

    if (ret == -2) return ESP_FAIL;
    return esp_mqtt_client_register_event(
        client,
        MQTT_EVENT_DATA,
        handler,
        NULL
    );
}

esp_err_t unsubscribe_mqtt5_topic(
    char *topic,
    int qos,
    void (*handler)(void*, esp_event_base_t, int32_t, void*)
) {
    return esp_mqtt_client_unregister_event(
        client,
        MQTT_EVENT_DATA,
        handler
    );
}