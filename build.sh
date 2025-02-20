#!/bin/bash

BUILD_DIR="build"

if [ ! -d $BUILD_DIR ]; then
    echo "Creating build folder"
    mkdir $BUILD_DIR
fi

cd build/
cmake -DCMAKE_TOOLCHAIN_FILE=..\toolchain\toolchain-linux.cmake -G "Unix Makefiles" ..
make
cd ..

chmod +x build/Z-Renderer
./build/Z-Renderer
