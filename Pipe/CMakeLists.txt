project(Pipe)
cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_COMPILE_OPTIONS "-pthread"
)
set(CMAKE_BUILD_TYPE Debug)
add_executable(${PROJECT_NAME} main.cpp)
