#include <mqtt_client.h>
#include <esp_log.h>

#define USE_PROPERTY_ARR_SIZE   sizeof(user_property_arr)/sizeof(esp_mqtt5_user_property_item_t)
#define BROKER_URL              CONFIG_BROKER_URL

static const char *TAG = "mqtt5";

static esp_mqtt_client_config_t mqtt_cfg = {
    .broker.address.uri = BROKER_URL,
};

static void __mqtt5_event_handler(
    void *arg,
    esp_event_base_t event_base,
    int32_t event_id,
    void *event_data
) {
    ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
}

void init_mqtt5(void) {
    esp_mqtt5_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, MQTT_EVENT_CONNECTED, __mqtt5_event_handler, NULL);
    esp_mqtt_client_start(client);
}