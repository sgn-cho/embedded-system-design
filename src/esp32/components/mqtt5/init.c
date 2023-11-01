#include <mqtt_client.h>

static esp_mqtt5_user_property_item_t user_property_arr[] = {
    {"board", "esp32"},
    {"u", "user"},
    {"p", "password"}
};

#define USE_PROPERTY_ARR_SIZE   sizeof(user_property_arr)/sizeof(esp_mqtt5_user_property_item_t)
#define BROKER_URL              CONFIG_BROKER_URL

static esp_mqtt_client_config_t mqtt5_cfg = {
    .broker.address.uri = BROKER_URL,
    .session.protocol_ver = MQTT_PROTOCOL_V_5,
    .network.disable_auto_reconnect = true,
    .credentials.username = "test",
    .credentials.authentication.password = "test",
    .session.last_will.topic = "/topic/will",
    .session.last_will.msg = "I will leave",
    .session.last_will.msg_len = 12,
    .session.last_will.qos = 1,
    .session.last_will.retain = true
};

static void init_mqtt5(void) {
    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt5_cfg);
}