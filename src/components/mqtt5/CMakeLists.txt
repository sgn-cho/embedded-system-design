idf_component_register(
    SRCS "event.c" "control.c"
    INCLUDE_DIRS "include"
    REQUIRES mqtt
)