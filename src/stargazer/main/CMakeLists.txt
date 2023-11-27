set(SRCS            main.c)
set(INCLUDE_DIRS    .
                    ../components
                    include
)

idf_component_register(
    SRCS ${SRCS}
    INCLUDE_DIRS ${INCLUDE_DIRS}
)