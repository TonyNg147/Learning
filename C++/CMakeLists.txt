project(BackTrace)
# cmake_minimum_required(VERSION 3.6)
# set(SOURCES main.cpp)
# set(CMAKE_BUILD_TYPE Debug)
# # list(APPEND CMAKE_CXX_FLAGS "-pthread")
# set(LDFLAGS "-rdynamic")
# add_executable(${PROJECT_NAME} ${SOURCES})
# target_link_libraries(${PROJECT_NAME} PRIVATE -ldl -lpthread)

set(SOURCES main.cpp
            TaskManager/TaskManager.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE -ldl -lpthread)
