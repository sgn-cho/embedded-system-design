#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include "include/test_camera.h"
#include "include/test_deep_learning.h"
#include "img_converters.h"
#include "initialize_camera.h"

const char *TAG = "main";

uint8_t *pixels;
uint8_t *src_buffer;

void app_main(void) {
    
}

void demo_test_code(void) {
    init_camera();
    take_picture("/sdcard/test.jpg");

    FILE *file = fopen("/sdcard/test.jpg", "rb");
    fseek(file, 0, SEEK_END);
    uint32_t size = ftell(file);
    rewind(file);

    src_buffer = (uint8_t*)malloc(size);
    fread(src_buffer, 1, size, file);
    fclose(file);

    ESP_LOGI(TAG, "esp_heap_free_size: %d", (int)esp_get_free_heap_size());
    pixels = NULL;
    pixels = (uint8_t*)calloc(1024 * 768 * 3, sizeof(uint8_t));

    if (pixels == NULL) ESP_LOGE(TAG, "pixels is NULL");
    else {
        fmt2rgb888(src_buffer, size, PIXFORMAT_JPEG, pixels);
        free(src_buffer);

        ESP_LOGI(TAG, "pixels: %d %d %d", pixels[0], pixels[1], pixels[2]);
        test_deep_learning(&pixels);
    }
}