#include <stdio.h>
#include <esp_log.h>
#include <esp_check.h>
#include <esp_system.h>
#include <esp_flash.h>
#include <nvs_flash.h>
#include <esp_netif.h>
#include <esp_event.h>

static const char *TAG = "system/init";


/* function prototypes */
static esp_err_t __init_prequisites(void);
static esp_err_t __init_netif(void);
static esp_err_t __init_event_loop(void);


void init_system(void) {
    __init_prequisites();
}

static esp_err_t __init_prequisites(void) {
    esp_err_t ret;

    ret = __init_nvs_flash();
    ESP_RETURN_ON_ERROR(ret, TAG, "__init_nvs_flash failed");

    ret = __init_netif();
    ESP_RETURN_ON_ERROR(ret, TAG, "__init_netif failed");

    ret = __init_event_loop();
    ESP_RETURN_ON_ERROR(ret, TAG, "__init_event_loop failed");
}

static esp_err_t __init_nvs_flash(void) {
    esp_err_t ret = nvs_flash_init();

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
        ret == ESP_ERR_NVS_NEW_VERSION_FOUND
    ) {
        ret = nvs_flash_erase();
        ESP_RETURN_ON_ERROR(ret, TAG, "nvs_flash_erase failed");

        ret = nvs_flash_init();
        ESP_RETURN_ON_ERROR(ret, TAG, "nvs_flash_init failed");
    }

    return ret;
}

static esp_err_t __init_netif(void) {
    return esp_netif_init();
}

static esp_err_t __init_event_loop(void) {
    return esp_event_loop_create_default();
}

static esp_err_t __init_application(void) {
    
}