#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>
#include <freertos/task.h>
#include <esp_event.h>
#include <driver/gptimer.h>
#include <esp_log.h>
#include <esp_check.h>
#include <msgd.h>
#include <device_address.h>

static const char *TAG = "sensord";

/* function prototypes */

static void __start_sensord(void);
static void __start_temperature_sensor(void);
static void __start_soil_sensor(void);
static void __mock_temperature_sensor(void *params);
static void __mock_soil_sensor(void *params);

/* end of function prototypes */

extern QueueHandle_t sensor_data_queue;

esp_err_t sensord_init(void) {
    esp_err_t ret = ESP_OK;
    ESP_LOGD(TAG, "Initializing msgd...");

    __start_sensord();
    ESP_LOGD(TAG, "Initialized sensord.");
    return ret;
}

void __start_sensord(void) {
    ESP_LOGD(TAG, "Starting sensord...");
    
    __start_temperature_sensor();
    __start_soil_sensor();
}

static void __start_temperature_sensor(void) {
    xTaskCreate(
        __mock_temperature_sensor,
        "temperature_sensor",
        2048,
        NULL,
        5,
        NULL
    );
}

static void __start_soil_sensor(void) {
    xTaskCreate(
        __mock_soil_sensor,
        "mock_soil_sensor",
        2048,
        NULL,
        5,
        NULL
    );
}

static void __mock_temperature_sensor(void *params) {
    ESP_LOGI(TAG, "Starting temperature sensor...");
    while (true) {
        ESP_LOGD(TAG, "Temperature sensor triggered.");
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
    vTaskDelete(NULL);
}

static void __mock_soil_sensor(void *params) {
    ESP_LOGI(TAG, "Starting soil sensor...");
    sensor_message_t test_data = {
        .route = SRC_SOIL_ADDR | DST_MQTT_ADDR,
        .data = 0x4F4C4548
    };

    while (true) {
        ESP_LOGD(TAG, "Soil sensor triggered.");
        BaseType_t ret = xQueueSend(
            sensor_data_queue,
            (void *)&test_data,
            portMAX_DELAY
        );
        if (ret != pdTRUE) ESP_LOGE(TAG, "Failed to send message.");
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
    vTaskDelete(NULL);
}
