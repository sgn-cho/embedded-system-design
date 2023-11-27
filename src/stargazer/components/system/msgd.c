#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_event.h>
#include <esp_log.h>
#include <esp_check.h>

#include "include/message.h"

static const char *TAG = "system/msgd";

QueueHandle_t sensor_data_queue;

#define MAX_QUEUE_LENGTH 10
#define SENSOR_QUEUE_SIZE sizeof(SensorData_t)


/* function prototypes */



void init_msgd(void) {
    sensor_data_queue = xQueueCreate(MAX_QUEUE_LENGTH, SENSOR_QUEUE_SIZE);
}

static void __msgd_sensor_loop(void) {
    if (sensor_data_queue == NULL) {
        ESP_LOGE(TAG, "sensor_data_queue is NULL");
        vTaskDelete(NULL);
    }

    SensorData_t sensor_data;
    while (true) {
        if (xQueueReceive(sensor_data_queue, &sensor_data, portMaxDelay) == pdTRUE) {
            ESP_LOGI(TAG, "Received sensor data: %d", sensor_data.value);
        }
    }
}