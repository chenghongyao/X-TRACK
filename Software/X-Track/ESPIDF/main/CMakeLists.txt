set(XTRACK_APP_DIR "../../USER/App")


file(GLOB XTRACK_SRCS 
    "${XTRACK_APP_DIR}/Common/DataProc/*.cpp"
    "${XTRACK_APP_DIR}/Common/Music/*.cpp"

    "${XTRACK_APP_DIR}/Pages/*.cpp"
    "${XTRACK_APP_DIR}/Pages/*/*.cpp"

    "${XTRACK_APP_DIR}/Utils/*/*.c"
    "${XTRACK_APP_DIR}/Utils/*/*.cpp"
    "${XTRACK_APP_DIR}/Utils/*/*/*.c"
    "${XTRACK_APP_DIR}/Utils/*/*/*.cpp"

    "${XTRACK_APP_DIR}/Resource/*.cpp"
    "${XTRACK_APP_DIR}/Resource/*/*.c"
)

file(GLOB HAL_SRCS
    "HAL/*.cpp"
)

idf_component_register(
    SRCS 
    "xtrack_main.cpp"
    "${XTRACK_APP_DIR}/App.cpp"
    ${HAL_SRCS}
    ${XTRACK_SRCS}


    INCLUDE_DIRS
    "./"
    "HAL"
    "${XTRACK_APP_DIR}/Utils/ArduinoJson/src"
    ${XTRACK_APP_DIR}
    )
