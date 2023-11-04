idf_component_register(
    SRCS "init.c"
    INCLUDE_DIRS "include"
    REQUIRES nvs_flash spi_flash esp_netif driver
)