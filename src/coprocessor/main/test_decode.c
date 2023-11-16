#include <esp_err.h>
#include <esp_vfs.h>
#include <esp_vfs_fat.h>
#include <esp_log.h>
#include <driver/sdmmc_host.h>
#include <driver/sdmmc_defs.h>
#include <sdmmc_cmd.h>
#include <sys/stat.h>
#include <esp_jpg_decode.h>
#include <jpeg_decoder.h>

const char *TAG = "test_decode";

#define IMAGE_H 320
#define IMAGE_W 240

/* function prototype */

static FILE* __open_file(char *file_name);
static uint32_t  __get_file_size(FILE *file);
static uint8_t* __read_file(FILE *file, uint32_t size);
static void __init_pixels(uint8_t **pixels);

/* end of function prototype */

void test_decode_task(uint8_t **pixels) {
    FILE *file = __open_file("/sdcard/pic_1.jpg");
    uint32_t size = __get_file_size(file);
    uint8_t *buffer = __read_file(file, size);

    __init_pixels(pixels);

    esp_jpeg_image_cfg_t jpeg_cfg = {
        .indata = (uint8_t *)buffer,
        .indata_size = size,
        .outbuf = (uint8_t *)(*pixels),
        .outbuf_size = IMAGE_H * IMAGE_W * sizeof(uint8_t) * 3,
        .out_format = JPEG_IMAGE_FORMAT_RGB888,
        .out_scale = JPEG_IMAGE_SCALE_0,
        .flags = {
            .swap_color_bytes = 1
        }
    };

    esp_jpeg_image_output_t outimg;
    esp_jpeg_decode(&jpeg_cfg, &outimg);
    free(buffer);

    ESP_LOGI(TAG, "%dpx x %dpx", outimg.width, outimg.height);
}

static FILE* __open_file(char *file_name) {
    return fopen(file_name, "r");
}

static uint32_t __get_file_size(FILE *file) {
    fseek(file, 0, SEEK_END);
    uint32_t size = ftell(file);
    rewind(file);
    return size;
}

static uint8_t* __read_file(FILE *file, uint32_t size) {
    uint8_t *buffer = malloc(size);
    fread(buffer, 1, size, file);
    fclose(file);
    return buffer;
}

static void __init_pixels(uint8_t **pixels) {
    *pixels = NULL;
    *pixels = calloc(IMAGE_H * IMAGE_W, sizeof(uint8_t) * 3);

    if ((*pixels) == NULL) {
        ESP_LOGE(TAG, "Failed to allocate memory for pixels");
        return;
    }
}