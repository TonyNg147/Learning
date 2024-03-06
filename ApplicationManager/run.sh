#!/bin/sh
if [ -d build ]; then
    cd build || exit
fi
QT=/home/as/Qt/6.2.4/gcc_64/
export PATH="${QT}/bin":"${PWD}/usr/share/bin":$PATH
export QT_PLUGIN_PATH=/home/as/Qt/6.2.4/gcc_64/./plugins
export LD_LIBRARY_PATH="${QT}/lib":"${PWD}/usr/share/lib":${LD_LIBRARY_PATH}
exec Home -c "${PWD}"/usr/share/am-config.yaml "qrc:/Qml/Qml/main.qml"
