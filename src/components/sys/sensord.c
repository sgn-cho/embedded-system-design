#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>
#include <freertos/task.h>
#include <esp_event.h>
#include <driver/gptimer.h>
#include <esp_log.h>
#include <esp_check.h>
#include <msgd.h>
#include <temperature/include/task.h>
#include <device_address.h>
#include <string.h>

static const char *TAG = "sensord";

/* function prototypes */

static void __start_sensord(void);
static esp_err_t __start_temperature_sensor(void);
static void __start_soil_sensor(void);
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

static esp_err_t __start_temperature_sensor(void) {
    ESP_RETURN_ON_ERROR(
        start_temperature_sensor(),
        TAG,
        "Failed to start temperature sensor."
    );
    return ESP_OK;
}

static void __start_soil_sensor(void) {
    xTaskCreate(
        __mock_soil_sensor,
        "mock_soil_sensor",
        4096,
        NULL,
        5,
        NULL
    );
}

static void __mock_temperature_sensor(void *params) {
    ESP_LOGI(TAG, "Starting temperature sensor...");

    double float_temperature;
    double float_humidity;

    new_sensor_message_t temperature_data = {
        .topic = "temperature_sensor",
        .length = 8,
        .data = 0
    };

    new_sensor_message_t humidity_data = {
        .topic = "humidity_sensor",
        .length = 8,
        .data = 0
    };

    while (true) {
        float_temperature = (double)rand()/(double)(RAND_MAX/100.0);
        float_humidity = (double)rand()/(double)(RAND_MAX/100.0);

        memcpy(&(temperature_data.data), &float_temperature, 8);
        memcpy(&(humidity_data.data), &float_humidity, 8);

        ESP_LOGD(TAG, "Temperature sensor triggered.");
        BaseType_t ret = xQueueSend(
            sensor_data_queue,
            (void *)&temperature_data,
            portMAX_DELAY
        );
        if (ret != pdTRUE) ESP_LOGE(TAG, "Failed to send message.");

        ret = xQueueSend(
            sensor_data_queue,
            (void *)&humidity_data,
            portMAX_DELAY
        );
        if (ret != pdTRUE) ESP_LOGE(TAG, "Failed to send message.");
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
    vTaskDelete(NULL);
}

static void __mock_soil_sensor(void *params) {
    ESP_LOGI(TAG, "Starting soil sensor...");

    double float_value;
    new_sensor_message_t test_data = {
        .topic = "soil_sensor",
        .length = 8,
        .data = 0
    };

    while (true) {
        float_value = (double)rand()/(double)(RAND_MAX/100.0);
        memcpy(&(test_data.data), &float_value, 8);

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
