idf_component_register(
    SRCS            initialize_camera.c
    INCLUDE_DIRS    ../../managed_components
                    include
    REQUIRES        esp_event
                    driver
                    sdmmc
                    fatfs
                    espressif__esp32-camera
)