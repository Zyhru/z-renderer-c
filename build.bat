@echo off
echo "Building project..."

cd build/
cmake .
cmake --build .
Debug\\Z-Renderer.exe
cd ..
