project(HMI)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(${PROJECT_NAME} STATIC)

qt6_add_qml_module(${PROJECT_NAME}
    URI "HMI"
    VERSION 1.0
    RESOURCE_PREFIX "/"
    NO_PLUGIN
    QML_FILES Inc.qml
    SOURCES service.cpp
)



message(PREfix + "${CMAKE_INSTALL_PREFIX}")

target_include_directories(${PROJECT_NAME} PUBLIC ./)


include(GNUInstallDirs)

message(LIB DIR + "${CMAKE_INSTALL_LIBDIR}")

install(TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
message(Project source dir + ${PROJECT_SOURCE_DIR})
set(git_result)
set(git_ver)
# execute_process(COMMAND abc.sh
#     WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
#     RESULT_VARIABLE git_result
#     OUTPUT_VARIABLE git_ver
# )

# add_custom_command(TARGET ${PROJECT_NAME} PRE_LINK
#                   WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
#                   COMMAND bash abc.sh
#                   VERSION)


install(SCRIPT demo.cmake
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)



