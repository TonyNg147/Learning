project(SysUI)

cmake_minimum_required(VERSION 3.6)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS AppManMainPrivate REQUIRED)
# qt6_am_add_systemui_wrapper(SysUI
#     NO_INSTALL 
#     CONFIG_YAML am-config.yaml
#     EXTRA_FILES apps system-ui
# )

install(FILES am-config.yaml
    DESTINATION "${CMAKE_BINARY_DIR}/usr/share"
)
add_subdirectory(ui-home)