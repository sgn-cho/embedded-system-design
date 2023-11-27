set(SRCS            init.c)
set(INCLUDE_DIRS    include)
set(REQUIRES        nvs_flash
                    spi_flash
                    esp_netif
                    driver
)

idf_component_register(
    SRCS ${SRCS}
    INCLUDE_DIRS ${INCLUDE_DIRS}
    REQUIRES ${REQUIRES}
)