#ifndef STAR_CAMERA_INIT_H_
#define STAR_CAMERA_INIT_H_

#include <esp_err.h>

esp_err_t init_camera(void);
esp_err_t take_picture(char *filepath);

#endif // STAR_CAMERA_INIT_H_
