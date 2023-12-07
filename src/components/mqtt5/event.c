#include <mqtt_client.h>
#include <esp_log.h>

static const char *TAG = "mqtt5";

void __mqtt5_sys_event_handler(
    void *arg,
    esp_event_base_t event_base,
    int32_t event_id,
    void *event_data
) {
    esp_mqtt_event_handle_t event = event_data;

    switch ((esp_mqtt_event_id_t)event_id) {
    case MQTT_EVENT_CONNECTED:
    /*    
        The client has successfully established a connection to the broker.
        The client is now ready to send and receive data.
    */
        ESP_LOGD(TAG, "MQTT event connected");
        break;

    case MQTT_EVENT_DISCONNECTED:
    /*
        The client has aborted the connection due to being unable to read or write data, 
        e.g., because the server is unavailable.
    */
        ESP_LOGD(TAG, "MQTT event disconnected");
        break;

    case MQTT_EVENT_PUBLISHED:
    /*
        The broker has acknowledged the client’s publish message. 
        This is only posted for QoS level 1 and 2, as level 0 does not use acknowledgements.
        The event data contains the message ID of the publish message.
    */
        ESP_LOGD(TAG, "MQTT event published");
        break;
        
    case MQTT_EVENT_ERROR:
        ESP_LOGW(TAG, "MQTT event error");
        break;

    default:
        ESP_LOGI(TAG, "Other event id:%d", event->event_id);
        break;
    }
}
