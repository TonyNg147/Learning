#!/bin/bash
read -p "Enter your name?" var
case $var in
    "a")
        echo "A"
        ;;
    "b")
        echo "B"
        ;;
    "c")
        echo "C"
        ;;
    *)
        echo "Default"
esac