idf_component_register(
    SRCS main.c test_wifi.c test_mqtt5.c
    INCLUDE_DIRS "." "../../components" "include" "../managed_components"
)

