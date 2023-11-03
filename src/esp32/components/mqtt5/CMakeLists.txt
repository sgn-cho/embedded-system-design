idf_component_register(
    SRCS "control.c" "init.c"
    INCLUDE_DIRS "include"
    REQUIRES mqtt
)