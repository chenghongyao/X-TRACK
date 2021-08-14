set(XTRACK_APP_DIR "../../USER/App")
set(XTRACK_LIB_DIR "../../Libraries")


file(GLOB_RECURSE XTRACK_UTILS_SRCS
    "${XTRACK_APP_DIR}/Utils/DataCenter/*.cpp"
    "${XTRACK_APP_DIR}/Utils/DataCenter/*.c"
    "${XTRACK_APP_DIR}/Utils/GPX/*.cpp"
    "${XTRACK_APP_DIR}/Utils/GPX_Parser/*.cpp"
    "${XTRACK_APP_DIR}/Utils/lv_ext/*.c"
    "${XTRACK_APP_DIR}/Utils/lv_ext/*.cpp"
    "${XTRACK_APP_DIR}/Utils/MapConv/*.cpp"
    "${XTRACK_APP_DIR}/Utils/MapConv/*.c"
    "${XTRACK_APP_DIR}/Utils/PageManager/*.cpp"
    "${XTRACK_APP_DIR}/Utils/StorageService/*.cpp"
    "${XTRACK_APP_DIR}/Utils/TileConv/*.cpp"
    "${XTRACK_APP_DIR}/Utils/TrackFilter/*.cpp"
    "${XTRACK_APP_DIR}/Utils/Time/*.cpp"
    "${XTRACK_APP_DIR}/Utils/TonePlayer/*.cpp"
    "${XTRACK_APP_DIR}/Utils/TonePlayer/*.cpp"
    )

    
file(GLOB XTRACK_SRCS 
    "${XTRACK_APP_DIR}/Common/DataProc/*.cpp"
    "${XTRACK_APP_DIR}/Common/Music/*.cpp"

    "${XTRACK_APP_DIR}/Pages/*.cpp"
    "${XTRACK_APP_DIR}/Pages/*/*.cpp"

    ${XTRACK_UTILS_SRCS}

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
    "${XTRACK_LIB_DIR}/TinyGPSPlus/src/TinyGPS++.cpp"
    "${XTRACK_LIB_DIR}/ButtonEvent/ButtonEvent.cpp"


    INCLUDE_DIRS
    "./"
    "HAL"
    ${XTRACK_APP_DIR}
    "${XTRACK_APP_DIR}/Utils/ArduinoJson/src"
    "${XTRACK_LIB_DIR}"
    )
