#!/bin/bash
cd ..

if [ ! -d "Build" ]; then
    mkdir Build
fi
cd Build

CMAKE_ARGS=$(cat ../Scripts/Common.txt | xargs)
cmake -G "Ninja" -B U64 $CMAKE_ARGS

cd U64

make
