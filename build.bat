@echo off
echo "Building project..."

cd build/
cmake .
cmake --build .
cd Debug/
Z-Renderer.exe
