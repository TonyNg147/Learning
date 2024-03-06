project(CustomQMl)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
list(APPEND SOURCES WindowCustom.h)
find_package(Qt6 COMPONENTS Gui REQUIRED Quick REQUIRED)
add_library(${PROJECT_NAME} STATIC)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Gui
                                      PRIVATE Qt6::Quick)
qt_add_qml_module(${PROJECT_NAME}
    URI "Customize"
    VERSION 1.0
    NO_PLUGIN
    SOURCES WindowCustom.h
            WindowCustom.cpp
    RESOURCE_PREFIX "/"
)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
