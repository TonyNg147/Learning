cmake_minimum_required(VERSION 3.6)

project(QmlLint)

set(SOURCES main.cpp HMI.qrc)

file(GLOB_RECURSE  QML_FILES ${PROJECT_SOURCE_DIR}/*.qml)

find_package(Qt6 REQUIRED COMPONENTS Quick)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(${PROJECT_NAME} ${SOURCES} HMI.qrc)

# add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
#                   COMMAND qmllint ${QML_FILES}
# )

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Quick)

