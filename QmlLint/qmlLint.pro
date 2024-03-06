QT+=quick

TARGET = QmlLint

SOURCES += main.cpp 

RESOURCES += HMI.qrc

QML_FILES = $$files($$PWD/*qml, true)

QMAKE_PRE_LINK = qmllint $${QML_FILES}

