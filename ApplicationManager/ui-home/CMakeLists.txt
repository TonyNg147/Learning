project(Home)
find_package(Qt6 COMPONENTS AppManMainPrivate REQUIRED)
qt_add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    Qt::AppManMainPrivate
)


qt6_add_qml_module(${PROJECT_NAME}
    VERSION 1.0
    URI Qml
    RESOURCE_PREFIX "/"
    QML_FILES 
        Qml/CenterDisplay.qml
        Qml/main.qml
    RESOURCES
        Qml/qmldir
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/usr/share/bin"
)





