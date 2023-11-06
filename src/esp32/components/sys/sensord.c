#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>
#include <freertos/task.h>
#include <esp_event.h>
#include <driver/gptimer.h>
#include <esp_log.h>
#include <esp_check.h>
#include "msgd.h"

static const char *TAG = "sensord";

EventGroupHandle_t sensor_event_group;
static gptimer_handle_t timer_handle;

#define TRIGGERED_TEMP_BIT BIT0
#define TRIGGERED_SOIL_BIT BIT1
#define TRIGGERED_CAMERA_BIT BIT2

/* function prototypes */

esp_err_t __init_timer(void);
static bool IRAM_ATTR __timer_callback(
    gptimer_handle_t timer,
    const gptimer_alarm_event_data_t *event_data,
    void *user_data
);
static void __start_sensord(void);
static void __start_temperature_sensor(void);
static void __start_soil_sensor(void);
static void __mock_temperature_sensor(void *params);
static void __mock_soil_sensor(void *params);

/* end of function prototypes */

esp_err_t sensord_init(void) {
    esp_err_t ret = ESP_OK;
    ESP_LOGD(TAG, "Initializing msgd...");

    sensor_event_group = xEventGroupCreate();
    ESP_LOGD(TAG, "Created event group");

    ret = __init_timer();
    ESP_RETURN_ON_ERROR(ret, TAG, "Failed to initialize timer: %d", ret);

    __start_sensord();
    ESP_LOGD(TAG, "Initialized sensord.");
    return ret;
}

esp_err_t __init_timer(void) {
    esp_err_t ret = ESP_OK;

    gptimer_config_t timer_config = {
    .clk_src = GPTIMER_CLK_SRC_DEFAULT,
    .direction = GPTIMER_COUNT_UP,
    .resolution_hz = 100000
    };

    ret = gptimer_new_timer(&timer_config, &timer_handle);
    ESP_RETURN_ON_ERROR(ret, TAG, "Failed to create timer: %d", ret);

    ret = gptimer_register_event_callbacks(
        timer_handle,
        &__timer_callback,
        NULL
    );
    ESP_RETURN_ON_ERROR(ret, TAG, "Failed to register timer callbacks: %d", ret);

    ret = gptimer_enable(timer_handle);
    ESP_RETURN_ON_ERROR(ret, TAG, "Failed to enable timer: %d", ret);

    gptimer_alarm_config_t alarm_config = {
        .reload_count = 0,
        .alarm_count = 1000000,
        .flags.auto_reload_on_alarm = true
    };
    ret = gptimer_set_alarm_action(timer_handle, &alarm_config);
    ESP_RETURN_ON_ERROR(ret, TAG, "Failed to set alarm action: %d", ret);

    ret = gptimer_start(timer_handle);
    ESP_RETURN_ON_ERROR(ret, TAG, "Failed to start timer: %d", ret);

    ESP_LOGD(TAG, "Initialized timer.");
    return ret;
}

void __start_sensord(void) {
    ESP_LOGD(TAG, "Starting sensord...");
    
    __start_temperature_sensor();
    __start_soil_sensor();
}

static bool IRAM_ATTR __timer_callback(
    gptimer_handle_t timer,
    const gptimer_alarm_event_data_t *event_data,
    void *user_data
) {
    xEventGroupSetBits(
        sensor_event_group,
        TRIGGERED_TEMP_BIT | TRIGGERED_SOIL_BIT
    );

    return true;
}

static void __start_temperature_sensor(void) {
    xTaskCreateStatic(
        __mock_temperature_sensor,
        "mock_temperature_sensor",
        1024,
        NULL,
        5,
        NULL,
        1
    );
}

static void __start_soil_sensor(void) {
    xTaskCreateStatic(
        __mock_soil_sensor,
        "mock_soil_sensor",
        1024,
        NULL,
        5,
        NULL,
        1
    );
}

static void __mock_temperature_sensor(void *params) {
    EventBits_t event_ret;
    
    while (true) {
        event_ret = xEventGroupWaitBits(
            sensor_event_group,
            TRIGGERED_TEMP_BIT,
            pdFALSE,
            pdFALSE,
            portMAX_DELAY
        );

        ESP_LOGD(TAG, "Temperature sensor triggered.");
        xEventGroupClearBits(sensor_event_group, TRIGGERED_TEMP_BIT);
    }
    vTaskDelete(NULL);
}

static void __mock_soil_sensor(void *params) {
    EventBits_t event_ret;

    while (true) {
        event_ret = xEventGroupWaitBits(
            sensor_event_group,
            TRIGGERED_SOIL_BIT,
            pdFALSE,
            pdFALSE,
            portMAX_DELAY
        );
        
        ESP_LOGD(TAG, "Soil sensor triggered.");
        xEventGroupClearBits(sensor_event_group, TRIGGERED_SOIL_BIT);
    }

    vTaskDelete(NULL);
}
