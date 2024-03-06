cmake_minimum_required(VERSION 3.16)
project(Demo)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


find_package(Qt6 COMPONENTS Quick Qml REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(HMI)

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})

qt6_add_qml_module(HMITest STATIC
    URI "Test"
    VERSION 1.0
    QML_FILES test.qml
    NO_PLUGIN
)

target_link_libraries(${PROJECT_NAME} PRIVATE HMI
                                              Qt6::Quick
                                              Qt6::Qml
                                              HMITest)

