cmake_minimum_required(VERSION 3.6)
project(SystemTest)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
message("Default Install Dir " ${CMAKE_INSTALL_PREFIX})
set(CMAKE_INSTALL_PREFIX "/home/as/Desktop/Learning/SystemD")
add_executable(${PROJECT_NAME} main.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER defines.h)
install(
    TARGETS ${PROJECT_NAME}
        PUBLIC_HEADER
            DESTINATION include
        RUNTIME
            DESTINATION usr/bin
)

