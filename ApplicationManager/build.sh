#!/bin/sh
/home/as/Qt/6.2.4/gcc_64/bin/qt-cmake -B build
cd build || exit
make install -j8
rm _SysUI.sh SysUI.sh &>/dev/null

    


