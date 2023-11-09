#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>
#include <freertos/task.h>
#include <esp_event.h>
#include <esp_log.h>
#include <esp_check.h>
#include <msgd.h>
#include "mqtt5/include/control.h"

static const char *TAG = "msgd";

QueueHandle_t sensor_data_queue;
QueueHandle_t camera_data_queue;

#define MAX_QUEUE_LENGTH 10
#define QUEUE_ITEM_SIZE sizeof(sensor_message_t)

/* function prototypes */

static void __msgd_loop_sensor(void);

/* end of function prototypes */

void msgd_init(void) {
    sensor_data_queue = xQueueCreate(MAX_QUEUE_LENGTH, QUEUE_ITEM_SIZE);

    xTaskCreate(
        __msgd_loop_sensor,
        "msgd_loop_sensor",
        2048,
        NULL,
        5,
        NULL
    );
}

static void __msgd_loop_sensor(void) {
    if (sensor_data_queue == NULL) {
        vTaskDelete(NULL);
        ESP_LOGE(TAG, "Sensor data queue is null.");
    }

    sensor_message_t msg;

    while(true) {
        if (xQueueReceive(sensor_data_queue, &msg, portMAX_DELAY) == pdTRUE) {
            ESP_LOGI(TAG, "Received message: %d", (int)msg.data);
            esp_err_t ret = publish_mqtt5_message(
                (char *)&msg.data,
                "sensor_data",
                0
            );
            ESP_LOGI(TAG, "%s", esp_err_to_name(ret));
        }
    }

    vTaskDelete(NULL);
}
