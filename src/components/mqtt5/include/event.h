#ifndef MQTT5_INIT_H_
#define MQTT5_INIT_H_

#include <mqtt_client.h>

void __mqtt5_sys_event_handler(
    void *arg,
    esp_event_base_t event_base,
    int32_t event_id,
    void *event_data
);

#endif
