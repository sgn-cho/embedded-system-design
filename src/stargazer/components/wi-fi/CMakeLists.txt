set(SRCS            init.c)
set(INCLUDE_DIRS    include)
set(REQUIRES        esp_wifi)

idf_component_register(
    SRCS ${SRCS}
    INCLUDE_DIRS ${INCLUDE_DIRS}
    REQUIRES ${REQUIRES}
)