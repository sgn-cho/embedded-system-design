#include <stdio.h>
#include <stdlib.h>
#include <esp_event.h>
#include <esp_log.h>
#include <esp_check.h>
#include "esp_system.h"
#include <sys/param.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/sdmmc_host.h"
#include "driver/sdmmc_defs.h"
#include "sdmmc_cmd.h"
#include "esp_vfs_fat.h"

#include "esp_camera.h"
#include "config.h"

static const char *TAG = "camera";
static const char mount_point[] = "/sdcard";

static camera_config_t camera_config = {
    .pin_pwdn = CAM_PIN_PWDN,
    .pin_reset = CAM_PIN_RESET,
    .pin_xclk = CAM_PIN_XCLK,
    .pin_sscb_sda = CAM_PIN_SIOD,
    .pin_sscb_scl = CAM_PIN_SIOC,

    .pin_d7 = CAM_PIN_D7,
    .pin_d6 = CAM_PIN_D6,
    .pin_d5 = CAM_PIN_D5,
    .pin_d4 = CAM_PIN_D4,
    .pin_d3 = CAM_PIN_D3,
    .pin_d2 = CAM_PIN_D2,
    .pin_d1 = CAM_PIN_D1,
    .pin_d0 = CAM_PIN_D0,
    .pin_vsync = CAM_PIN_VSYNC,
    .pin_href = CAM_PIN_HREF,
    .pin_pclk = CAM_PIN_PCLK,

    //XCLK 20MHz or 10MHz for OV2640 double FPS (Experimental)
    .xclk_freq_hz = 20000000,
    .ledc_timer = LEDC_TIMER_0,
    .ledc_channel = LEDC_CHANNEL_0,

    .pixel_format = PIXFORMAT_JPEG, //YUV422,GRAYSCALE,RGB565,JPEG
    .frame_size = FRAMESIZE_XGA,    //QQVGA-UXGA Do not use sizes above QVGA when not JPEG

    .jpeg_quality = 6, //0-63 lower number means higher quality
    .fb_count = 1       //if more than one, i2s runs in continuous mode. Use only with JPEG
};

/* function prototype */

static esp_err_t init_camera_driver(void);
static esp_err_t init_sdcard(void);
static void init_gpio(void);

/* end of function prototype */

esp_err_t init_camera(void) {
    esp_err_t ret;

    ret = init_camera_driver();
    if (ret == ESP_OK) ret = init_sdcard();

    return ret;
}

esp_err_t take_picture(char *filepath) {
    camera_fb_t *picture = esp_camera_fb_get();
    FILE *file = fopen(filepath, "w");

    if (file != NULL) {
        fwrite(picture->buf, 1, picture->len, file);
        ESP_LOGI(TAG, "File saved: %s", filepath);
        free(picture->buf);
        fclose(file);
        return ESP_OK;
    } 
    else {
        ESP_LOGE(TAG, "Failed to open file for writing");
        free(picture->buf);
        fclose(file);
        return ESP_FAIL;
    }
}

static esp_err_t init_camera_driver(void) {
    esp_err_t ret = esp_camera_init(&camera_config);
    ESP_RETURN_ON_ERROR(ret, TAG, "Camera init failed with error");

    return ESP_OK;
}

static esp_err_t init_sdcard(void) {
    esp_err_t ret;

    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files = 5,
        .allocation_unit_size = 16 * 1024
    };
    sdmmc_card_t *card;

    sdmmc_host_t host = SDMMC_HOST_DEFAULT();
    sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();

    init_gpio();

    ret = esp_vfs_fat_sdmmc_mount(
        mount_point,
        &host,
        &slot_config,
        &mount_config,
        &card);
    
    ESP_RETURN_ON_ERROR(ret, TAG, "SD card mount failed with error");

    return ESP_OK;
}

static void init_gpio(void) {
    gpio_set_pull_mode(15, GPIO_PULLUP_ONLY);   // CMD, needed in 4- and 1- line modes
    gpio_set_pull_mode(2, GPIO_PULLUP_ONLY);    // D0, needed in 4- and 1-line modes
    gpio_set_pull_mode(4, GPIO_PULLUP_ONLY);    // D1, needed in 4-line mode only
    gpio_set_pull_mode(12, GPIO_PULLUP_ONLY);   // D2, needed in 4-line mode only
    gpio_set_pull_mode(13, GPIO_PULLUP_ONLY);   // D3, needed in 4- and 1-line modes
}