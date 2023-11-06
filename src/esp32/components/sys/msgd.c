#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>
#include <freertos/task.h>
#include <esp_event.h>
#include <esp_log.h>

static const char *TAG = "msgd";
EventGroupHandle_t message_event_group;
QueueHandle_t sensor_data_queue;
QueueHandle_t camera_data_queue;

void msgd_init(void) {
    message_event_group = xEventGroupCreate();
}
