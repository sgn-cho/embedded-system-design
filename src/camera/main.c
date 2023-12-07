#include <stdio.h>
#include <stdlib.h>
#include "camera_task_1.c"

void app_main(void){
    xTaskCreate(task1, "camera_task", 2048, NULL, 1, NULL);
    }