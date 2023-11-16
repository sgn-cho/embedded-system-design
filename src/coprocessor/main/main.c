#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "include/test_camera.h"
#include "include/test_decode.h"
#include "include/test_deep_learning.h"

uint8_t *pixels;

void app_main(void) {
    printf("Hello world!\n");
    task1();
    test_decode_task(&pixels);
    test_deep_learning(&pixels);
}