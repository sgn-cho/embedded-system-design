idf_component_register(
    SRCS task.c measurement.c
    INCLUDE_DIRS "include" "../"
    REQUIRES spi_flash driver dht
)