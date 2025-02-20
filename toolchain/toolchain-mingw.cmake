set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

find_program(
    GCC_EXECUTABLE NAMES gcc
    PATHS "C:/msys64/mingw64/bin"
    DOC "Path to GCC executable"
)

if(GCC_EXECUTABLE)
    message(STATUS "Found GCC: ${GCC_EXECUTABLE}")
else()
    message(WARNING "GCC not found.")
endif()

# Specify the cross-compiler
set(CMAKE_C_COMPILER ${GCC_EXECUTABLE})
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_FIND_ROOT_PATH "C:/msys64/mingw64")
set(CMAKE_CXX_FLAGS_INIT "Werror=array-bounds=")

# Werror=array-bounds=

# Set other necessary flags
set(CMAKE_C_FLAGS "-Wall -Werror=array-bounds -Wextra -O2")
set(CMAKE_CXX_FLAGS "-Wall -Werror=array-bounds -Wextra -O2")

# Make sure CMake doesn't try to use MSVC
set(CMAKE_GENERATOR "MinGW Makefiles")
