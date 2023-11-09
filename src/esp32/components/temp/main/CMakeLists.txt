idf_component_register(
    SRCS "main.c" "measurement_task.c" "algorithm.c" "measurement.c" "platform_measurement_dht.c"
    INCLUDE_DIRS "."
    REQUIRES nvs_flash esp_netif esp_pm driver
)
