#ifndef WIFI_HANDLER_H_
#define WIFI_HANDLER_H_

#include <esp_event.h>

void __wifi_event_handler(
    void *arg,
    esp_event_base_t event_base,
    int32_t event_id,
    void *event_data
);

void __ip_event_handler(
    void *arg,
    esp_event_base_t event_base,
    int32_t event_id,
    void *event_data
)

#endif // WIFI_HANDLER_H_
