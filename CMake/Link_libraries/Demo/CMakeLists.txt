set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(DemoLib SHARED DemoHeader.cpp)

target_include_directories(DemoLib PUBLIC 
./
)