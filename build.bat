@echo off
echo "Building project..."
echo "MODE = Release"

cd build/
cmake .
cmake --build .
Debug\\Z-Renderer.exe
cd ..
