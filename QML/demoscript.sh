#!/bin/bash

files=("ABC" "XYZ")

for file in "${files[@]}"
do
    echo "File is " + ${file}
done