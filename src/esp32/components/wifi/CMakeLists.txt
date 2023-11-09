idf_component_register(
    SRCS "ap.c" "init.c"
    INCLUDE_DIRS "include"
    PRIV_REQUIRES esp_wifi
)