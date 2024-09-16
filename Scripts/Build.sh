#!/bin/bash
cd ..

CMAKE_ARGS=$(cat ../Scripts/Common.txt | xargs)
cmake -G "Ninja" -B Build $CMAKE_ARGS

cmake --build Build
