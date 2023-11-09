#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <measurement.h>
#include <esp_log.h>
#include <esp_check.h>
#include <esp_pm.h>
#include <stdbool.h>
#include <dht/dht.h>

#define DHT_SENSOR_TYPE DHT_TYPE_AM2301
#define DHT_GPIO_NUM GPIO_NUM_18

static const char *TAG = "temperature measurement";

static measurement_config_t current_config;

/* function prototypes */

static esp_err_t __read_sensor_value(float *temp, float *humidity);
static esp_err_t __read_single_value(float *temp, float *humidity);
static esp_err_t __read_single_raw_value(int16_t *temp, int16_t *humidity);

/* end of function prototypes */

esp_err_t init_measurement(measurement_config_t config) {
    if (config.interval_ms == 0) {
        return ESP_ERR_INVALID_ARG;
    }

    current_config = config;
    return ESP_OK;
}

void task_temperature_measurement(void *params) {
    while(true) {
        float temp, humidity;
        esp_err_t ret = __read_sensor_value(&temp, &humidity);

        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "Failed to read sensor value.");
        } else {
            ESP_LOGD(TAG, "Temperature: %f, Humidity: %f", temp, humidity);
            
        }

        vTaskDelay(pdMS_TO_TICKS(current_config.interval_ms));
    }
    vTaskDelete(NULL);
}

static esp_err_t __read_sensor_value(float *temp, float *humidity) {
    esp_pm_lock_handle_t lock_handle;

    esp_pm_lock_create(ESP_PM_APB_FREQ_MAX, 0, "temp_sensor", &lock_handle);
    esp_pm_lock_acquire(lock_handle);

    esp_err_t ret = __read_single_value(temp, humidity);
    esp_pm_lock_release(lock_handle);

    return ret;
}

static esp_err_t __read_single_value(float *temp, float *humidity) {
    int16_t temp_raw;
    int16_t humidity_raw;

    esp_err_t ret = __read_single_raw_value(&temp_raw, &humidity_raw);
    ESP_RETURN_ON_ERROR(ret, TAG, "Failed to read raw value.");

    *temp = ((float)temp_raw) / 10.0;
    *humidity = ((float)humidity_raw) / 10.0;

    return ESP_OK;
}

static esp_err_t __read_single_raw_value(int16_t *temp, int16_t *humidity) {
    esp_err_t ret = dht_read_data(DHT_TYPE_DHT11, DHT_GPIO_NUM, humidity, temp);
    return ret;
}