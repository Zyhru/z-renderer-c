#!/bin/bash

echo "Building Z-Renderer for Linux"
echo "MODE = RELEASE"

cd build/
cmake -DCMAKE_BUILD_TYPE=Release ..

cmake --build .
Debug/./Z-Renderer
cd ..
