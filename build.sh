#!/bin/bash

mkdir -p build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain/toolchain-linux.cmake -G "Unix Makefiles" ..
make
cd ..

chmod +x build/Z-Renderer
./build/Z-Renderer
