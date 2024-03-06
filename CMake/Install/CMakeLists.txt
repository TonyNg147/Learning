project(INSTALL_DEMO)

cmake_minimum_required(VERSION 3.6)

set(SOURCES main.cpp)
set(DESTDIT ${PROJECT_BINARY_DIR}/target)

add_executable(${PROJECT_NAME} ${SOURCES})


if(NOT TEST)
    message(WARNING "TEST is not defined")
else()
    message("Test is defined with valuesss "  ${TEST})
    target_compile_definitions(${PROJECT_NAME} PRIVATE NGUYEN)
endif()

set(CMAKE_INSTALL_PREFIX "/usr")
include(GNUInstallDirs)
message("Install prefix " + ${CMAKE_INSTALL_PREFIX})
message("CMAKE_INSTALL_LIBDIR " + ${CMAKE_INSTALL_LIBDIR})
message("CMAKE_INSTALL_BINDIR " + ${CMAKE_INSTALL_BINDIR})

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION  ${CMAKE_INSTALL_BINDIR}
)


function(Nguyen)
    message("Call Nguyen with number of Arguments " ${ARGC})
    foreach(Idx RANGE 0 ARGC)
        message("Variable is " "${ARGV+${Idx}}")
    endforeach(Idx RANGE 0 ARGC)
endfunction()

Nguyen(a b c)
