project(Logger)

set(SOURCE Sources/CoreDumpHandler.cpp
            Sources/ConsoleSink.cpp
            Sources/Logger.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCE})

target_link_libraries(${PROJECT_NAME} PUBLIC -ldl -pthread)

target_include_directories(${PROJECT_NAME} PUBLIC Headers)

set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_CXX_FLAGS -rdynamic)