cmake_minimum_required(VERSION 3.6)
project(USB_SVR_VIEW)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_PREFIX_PATH /home/as/Qt/6.2.4/gcc_64)

add_subdirectory(CustomQMl)
add_subdirectory(Feature)

list(APPEND SOURCES raster.cpp main.cpp)
find_package(Qt6 COMPONENTS Gui REQUIRED Quick REQUIRED)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Gui
                                      PRIVATE Qt6::Quick
                                      PRIVATE CustomQMl)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR})
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION usr/bin
)


qt_add_qml_module(${PROJECT_NAME}
    URI HMI
    VERSION 1.0
    RESOURCE_PREFIX "/"
    QML_FILES main.qml
)