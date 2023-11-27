set(SRCS    main.c
            test_camera.c
            test_deep_learning.cpp
)

set(INCLUDE_DIRS    .
                    ../../components
                    include
                    ../managed_components
)

idf_component_register(
    SRCS ${SRCS}
    INCLUDE_DIRS ${INCLUDE_DIRS}
)