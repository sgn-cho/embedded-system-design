idf_component_register(
    SRCS            detect_face.cpp
    INCLUDE_DIRS    .
                    ./include
                    ./include/tool
                    ./include/nn
                    ./include/layer
                    ./include/image
                    ./include/typedef
                    ./include/detect
                    ./include/model_zoo
    REQUIRES        driver
                    esp_timer
)

if (${IDF_TARGET} STREQUAL "esp32")
    set(links   "-L ${CMAKE_CURRENT_SOURCE_DIR}/lib/esp32")
elseif (${IDF_TARGET} STREQUAL "esp32s2")
    set(links   "-L ${CMAKE_CURRENT_SOURCE_DIR}/lib/esp32s2")
elseif (${IDF_TARGET} STREQUAL "esp32s3")
    set(links   "-L ${CMAKE_CURRENT_SOURCE_DIR}/lib/esp32s3")
elseif (${IDF_TARGET} STREQUAL "esp32c3")
    set(links   "-L ${CMAKE_CURRENT_SOURCE_DIR}/lib/esp32c3")
endif()

set(
    lib     libhuman_face_detect.a
            libdl.a
)

target_link_libraries(${COMPONENT_TARGET} ${links})
target_link_libraries(${COMPONENT_TARGET} ${lib})
