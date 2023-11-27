#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/event_groups.h>
#include <esp_event.h>
#include <esp_log.h>
#include <esp_err.h>
#include <esp_check.h>

#include "camera/include/image_type.h"
#include "mqtt5/include/control.h"

static const char *TAG = "msgd";

QueueHandle_t camera_data_queue;
QueueHandle_t command_queue;

#define MAX_QUEUE_LENGTH 10
#define CAMERA_QUEUE_ITEM_SIZE sizeof(camera_image_t)

/* function prototypes */

static void __msgd_loop(void);

/* end of function prototypes */

void init_msgd(void) {
    camera_data_queue = xQueueCreate(MAX_QUEUE_LENGTH, CAMERA_QUEUE_ITEM_SIZE);

    xTaskCreate(__msgd_loop, "msgd_loop", 4096, NULL, 5, NULL);
}

// reference: https://www.home-assistant.io/integrations/camera.mqtt/
static void __msgd_loop(void) {
    camera_image_t image_message;
    BaseType_t ret_queue;
    esp_err_t ret_mqtt;

    while (true) {
        ret_queue = xQueueReceive(camera_data_queue, &image_message, portMAX_DELAY);

        if (ret_queue == pdTRUE) {
            ret_mqtt = publish
        }
    }
}