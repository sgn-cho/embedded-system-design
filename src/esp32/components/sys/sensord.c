#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>
#include <freertos/task.h>
#include <esp_event.h>
#include <esp_log.h>

static const char *TAG = "sensord";
EventGroupHandle_t sensor_event_group;

#define TIMER_EXPIRED_BIT BIT0

/* function prototypes */

static void __start_temperature_sensor(void);
static void __start_camera_sensor(void);
static void __start_soil_sensor(void);

/* end of function prototypes */

void sensord_init(void) {
    ESP_LOGD(TAG, "Initializing msgd...");

    sensor_event_group = xEventGroupCreate();
    ESP_LOGD(TAG, "Created event group");

    ESP_LOGD(TAG, "Initialized msgd");
}

void sensord_start(void) {
    ESP_LOGD(TAG, "Starting sensord...");
    
    __start_temperature_sensor();
    __start_camera_sensor();
    __start_soil_sensor();
}

void __start_temperature_sensor(void) {

}

void __start_camera_sensor(void) {

}

void __start_soil_sensor(void) {

}
