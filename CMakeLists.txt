cmake_minimum_required(VERSION 3.29)
project(Z-Renderer)

message(STATUS "v1: CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")

# Set CMAKE_C_COMPILER path based on OS
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    find_program(
                GCC_EXECUTABLE NAMES gcc
                PATHS "C:/msys64/mingw64/bin"
                DOC "Path to GCC executable"
    )

elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    find_program(
                GCC_EXECUTABLE NAMES gcc
                PATHS /usr/bin
                DOC "Path to GCC executable"
    )
endif()

if(GCC_EXECUTABLE)
    message(STATUS "Found GCC: ${GCC_EXECUTABLE}")
else()
    message(WARNING "GCC not found.")
endif()

set(CMAKE_C_COMPILER ${GCC_EXECUTABLE})
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

##############################################################

# FetchContent module to download external dependencies
include(FetchContent)

# Fetch GLAD (OpenGL loader)
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG        v0.1.34  # Latest stable version
)
FetchContent_MakeAvailable(glad)

# Fetch GLFW (OpenGL windowing library)
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.3.8  # Latest stable version
)
FetchContent_MakeAvailable(glfw)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Fetch cglm (mathematics library for OpenGL)
FetchContent_Declare(
  cglm
  GIT_REPOSITORY https://github.com/recp/cglm.git
  GIT_TAG        v0.8.2  # Latest stable version (update as necessary)
)
FetchContent_MakeAvailable(cglm)

# Add executable (point this to your source file)
add_executable(Z-Renderer 
    src/main.c
    src/window.c
    src/renderer.c
    src/util.c
    src/camera.c
    src/input.c
    src/model.c
)

# Include directories for GLAD and GLFW
target_include_directories(Z-Renderer PUBLIC ${glad_SOURCE_DIR}/include)
target_include_directories(Z-Renderer PUBLIC ${glfw_SOURCE_DIR}/include)
target_include_directories(Z-Renderer PUBLIC ${cglm_SOURCE_DIR}/include)

# Link the libraries (GLFW, GLAD, and OpenGL)
find_package(OpenGL REQUIRED)
target_link_libraries(Z-Renderer glfw glad OpenGL::GL)

# Windows-specific linking (gdi32 for OpenGL)
if (WIN32)
   target_link_libraries(Z-Renderer gdi32)
endif()

