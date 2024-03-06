project(Link)

set(SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/Demo)

target_link_libraries(${PROJECT_NAME} PRIVATE DemoLib)

# add_dependencies(${PROJECT_NAME} DemoLib)

add_subdirectory(Demo)