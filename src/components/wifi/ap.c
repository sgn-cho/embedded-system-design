#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include "esp_mac.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_check.h"

#include "lwip/err.h"
#include "lwip/sys.h"

static const char *TAG = "Wi-Fi AP";

static void wifi_event_handler(
    void *arg,
    esp_event_base_t event_base,
    int32_t event_id,
    void *event_data
) {
    if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t *event 
            = (wifi_event_ap_staconnected_t*) event_data;
        
        ESP_LOGI(TAG, "station "MACSTR" join, AID=%d",
                MAC2STR(event->mac), event->aid);
    } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t *event
            = (wifi_event_ap_stadisconnected_t*) event_data;

        ESP_LOGI(TAG, "station "MACSTR" leave, AID=%d",
                MAC2STR(event->mac), event->aid);
    }
}

esp_err_t wifi_init_softap(void) {
    esp_err_t ret;
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ret = esp_wifi_init(&cfg);
    ESP_RETURN_ON_ERROR(ret, TAG, "esp_wifi_init failed");

    ret = esp_event_handler_instance_register(
        WIFI_EVENT,
        ESP_EVENT_ANY_ID,
        &wifi_event_handler,
        NULL,
        NULL
    );
    ESP_RETURN_ON_ERROR(ret, TAG, "esp_event_handler_instance_register failed");

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = "test-wifi",
            .ssid_len = strlen("test-wifi"),
            .channel = 11,
            .password = "test-wifi-ing",
            .max_connection = 4,
            .authmode = WIFI_AUTH_WPA2_PSK,
            .pmf_cfg = { .required = true }
        }
    };

    ret = esp_wifi_set_mode(WIFI_MODE_AP);
    ESP_RETURN_ON_ERROR(ret, TAG, "esp_wifi_set_mode failed");

    ret = esp_wifi_set_config(WIFI_IF_AP, &wifi_config);
    ESP_RETURN_ON_ERROR(ret, TAG, "esp_wifi_set_config failed");

    ret = esp_wifi_start();
    ESP_RETURN_ON_ERROR(ret, TAG, "esp_wifi_start failed");

    return ESP_OK;
}