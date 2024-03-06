set(CPP_SOURCES
    Student.h
    Student.cpp
    Location.h
    Location.cpp
)

qt6_add_qml_module(AcademyControlBlock STATIC
    URI "AcademyControlBlock"
    VERSION 1.0
    SOURCES
        ${CPP_SOURCES}
    NO_PLUGIN
)

target_include_directories(AcademyControlBlock PUBLIC .)