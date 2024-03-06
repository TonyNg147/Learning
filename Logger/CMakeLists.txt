cmake_minimum_required(VERSION 3.6)
project(CoreDump)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

set(SOURCES main.cpp)

set(CMAKE_BUILD_TYPE "Debug")

add_executable(${PROJECT_NAME} ${SOURCES})

add_subdirectory(Logger)

target_link_libraries(${PROJECT_NAME} PRIVATE Logger)
