#include <mqtt_client.h>
#include <esp_log.h>
#include <esp_err.h>
#include <esp_check.h>

extern esp_mqtt_client_handle_t __mqtt5_client;

esp_err_t publish_mqtt5_message(
    char *message,
    char *topic,
    int length,
    int qos,
    int retain
) {
    if (qos == 1 || qos == 2) {
        ESP_LOGE(TAG, "QoS %d not supported", qos);
        return ESP_FAIL;
    }

    int msg_id = esp_mqtt_client_publish(
        __mqtt5_client,
        topic,
        message,
        length,
        qos,
        retain
    );

    if (msg_id == -1) {
        ESP_LOGE(TAG, "Failed to publish message");
        return ESP_FAIL;
    }

    return ESP_OK;
}