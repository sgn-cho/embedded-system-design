#ifndef CAMERA_IMAGE_TYPE_H_
#define CAMERA_IMAGE_TYPE_H_

#include <esp_camera.h>

typedef struct {
    uint8_t *buffer;
    size_t len;
    uint8_t width;
    uint8_t height;
} camera_image_t;

#endif  // CAMERA_IMAGE_TYPE_H_

// 3584