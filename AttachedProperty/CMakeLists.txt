cmake_minimum_required(VERSION 3.6)

project(AttachedProperty)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Quick Qml REQUIRED)

set(SOURCES
    main.cpp
    HMI.qrc
)
add_subdirectory(School)


add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE QT_QML_DEBUG)


target_link_libraries(${PROJECT_NAME} 
    PRIVATE Qt6::Quick
            Qt6::Qml
            AcademyControlBlock
)

