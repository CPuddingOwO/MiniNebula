@echo off

cd ..

setlocal enabledelayedexpansion
set CMAKE_ARGS=
for /f "usebackq delims=" %%i in ("./Scripts/Common.txt") do (
    set "CMAKE_ARGS=!CMAKE_ARGS! %%i"
)

cmake -G "Ninja" -B Build %CMAKE_ARGS%

cmake --build Build

cd Build

if not exist compiled mkdir compiled


