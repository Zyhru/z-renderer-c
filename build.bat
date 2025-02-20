@echo off

REM if build folder does not exist, create the folder

set BUILD_DIR=build

if NOT EXIST "%BUILD_DIR%" (
    echo "Creating build folder"
    mkdir "%BUILD_DIR%"
)

REM Building

cd build
cmake -DCMAKE_TOOLCHAIN_FILE=..\toolchain\toolchain-mingw.cmake -G "MinGW Makefiles" ..
REM cmake --build .
mingw32-make
cd ..

build\\Z-Renderer.exe
