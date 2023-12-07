idf_component_register(
    SRCS "msgd.c" "sensord.c" "init.c"
    INCLUDE_DIRS "include" "../"
    REQUIRES nvs_flash spi_flash esp_netif driver
)