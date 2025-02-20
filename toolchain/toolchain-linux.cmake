set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

# Specify the cross-compiler
set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)


# Set other necessary flags
set(CMAKE_C_FLAGS "-Wall  -Wextra -O2")
set(CMAKE_CXX_FLAGS "-Wall  -Wextra -O2")

# Make sure CMake doesn't try to use MSVC
set(CMAKE_GENERATOR "Unix Makefiles")

