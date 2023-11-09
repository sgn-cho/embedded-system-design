#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_pm.h>
#include <esp_log.h>
#include <esp_check.h>
#include <measurement.h>

static const char* TAG = "temperature sensor";

/* function prototypes */

static esp_err_t __init_temperature_sensor(void);
static esp_err_t __init_power_mgmt(void);
static esp_err_t __start_measurement(void);

/* end of function prototypes */

esp_err_t start_temperature_sensor(void) {
    esp_err_t ret;
    
    ret = __init_temperature_sensor();

    return ESP_OK;
}

static esp_err_t __init_temperature_sensor(void) {
    esp_err_t ret;

#ifdef CONFIG_PM_ENABLE
    ret = __power_mgmt_init();
    ESP_RETURN_ON_ERROR(ret, TAG, "Failed to initialize power management.");
#endif

    measurement_config_t config = {
        .interval_ms = CONFIG_MEASUREMENT_INTERVAL,
        .utc_offset_ms = CONFIG_MEASUREMENT_OFFSET
    };

    ret = init_measurement(config);
    ESP_RETURN_ON_ERROR(ret, TAG, "Failed to initialize measurement.");

    ret = __start_measurement();
    ESP_RETURN_ON_ERROR(ret, TAG, "Failed to start measurement.");

    return ESP_OK;
}

static esp_err_t __init_power_mgmt(void) {
    esp_pm_config_t pm_config;
	pm_config.max_freq_mhz = 80;
	pm_config.min_freq_mhz = 10;
	pm_config.light_sleep_enable = true;

    return esp_pm_configure(&pm_config);
}

static esp_err_t __start_measurement(void) {
    BaseType_t ret = xTaskCreate(
        task_temperature_measurement,
        "temperature_measurement",
        2048,
        NULL,
        5,
        NULL
    );

    if (ret != pdPASS) {
        ESP_LOGE(TAG, "Failed to start measurement task.");
        return ESP_FAIL;
    } 
    else return ESP_OK;

}