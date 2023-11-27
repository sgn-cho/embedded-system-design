#ifndef MQTT5_CLIENT_HANDLER_H_
#define MQTT5_CLIENT_HANDLER_H_

#include <esp_event.h>

void __mqtt5_sys_event_handler(
    void *arg,
    esp_event_base_t event_base,
    int32_t event_id,
    void *event_data
);

#endif // MQTT5_CLIENT_HANDLER_H_