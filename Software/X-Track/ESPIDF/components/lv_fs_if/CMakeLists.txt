idf_component_register(
    SRCS 
    "lv_fs_fatfs.c"
    "lv_fs_pc.c"
    "lv_fs_posix.c"
    "lv_fs_if.c"
    
    INCLUDE_DIRS
    "./"

    REQUIRES
    lvgl
    )