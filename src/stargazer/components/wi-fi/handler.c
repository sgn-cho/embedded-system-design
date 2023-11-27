#include <freertos/event_groups.h>
#include <esp_wifi.h>
#include <esp_err.h>
#include <esp_check.h>

extern EventGroupHandle_t wifi_event_group;
extern WIFI_FAIL_BIT;

static int retry_num = 0;

void __wifi_event_handler(
    void *arg,
    esp_event_base_t event_base,
    int32_t event_id,
    void *event_data
) {
    if (event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_id == WIFI_EVENT_STA_DISCONNECTED) {
        __recover_wifi_connection();
        ESP_LOGI(TAG, "Wi-Fi disconnected");
    }
}

static void __recover_wifi_connection(void) {
    if (retry_num < CONFIG_WIFI_MAXIMUM_RETRY) {
        ESP_LOGI(TAG, "retry to connect to the AP");
        esp_wifi_connect();
        retry_num++;
    } else {
        xEventGroupSetBits(wifi_event_group, WIFI_FAIL_BIT);
    }
}

void __ip_event_handler(
    void *arg,
    esp_event_base_t event_base,
    int32_t event_id,
    void *event_data
) {
    if (event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
        ESP_LOGI(TAG, "got ip: " IPSTR, IP2STR(&event->ip_info.ip));
        retry_num = 0;
        xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);
    }
}