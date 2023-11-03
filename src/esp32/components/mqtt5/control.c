#include <mqtt_client.h>
#include <esp_log.h>
#include "./init.h"

#ifndef BROKER_URL
#define BROKER_URL              CONFIG_BROKER_URL    
#endif

typedef struct connection_info_t {
    char *topic;
    int connection_cnt;
} connection_info_t;

static const char *TAG = "mqtt5";
static esp_mqtt5_client_handle_t client;

/* function prototypes */

void __init_mqtt5(esp_mqtt_client_config_t *cfg);

/* end of function prototypes */

void init_mqtt5(void) {
    esp_mqtt_client_config_t cfg = {
        .broker.address.uri = BROKER_URL,
    };

    __init_mqtt5(&cfg);
}

void __init_mqtt5(esp_mqtt_client_config_t *cfg) {
    client = esp_mqtt_client_init(cfg);
    esp_mqtt_client_register_event(client, MQTT_EVENT_CONNECTED, __mqtt5_sys_event_handler, NULL);
    esp_mqtt_client_start(client);
}

esp_err_t publish_mqtt5_message(char *message, char *topic, int qos) {
    int message_id = esp_mqtt_client_publish(client, topic, message, 0, qos, 0);

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