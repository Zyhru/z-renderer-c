@echo off

REM if build folder does not exist, create the folder

set BUILD_DIR=/build

if NOT EXIST "%BUILD_DIR%" (
    echo "Creating build folder"
    mkdir "%BUILD_DIR%"
)

REM Building

cd build
cmake ..
cmake --build .
cd ..

build\\Debug\\Z-Renderer.exe
