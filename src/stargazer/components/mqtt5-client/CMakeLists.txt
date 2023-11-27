set(SRCS            init.c)
set(INCLUDE_DIRS    include)
set(REQUIRES        mqtt)

idf_component_register(
    SRCS ${SRCS}
    INCLUDE_DIRS ${INCLUDE_DIRS}
    REQUIRES ${REQUIRES}
)