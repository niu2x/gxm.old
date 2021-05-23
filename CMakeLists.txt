cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)

project(GXM VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(glfw3)
find_package(OpenGL)
find_package(GLEW)
find_package(Threads)
find_package(Boost COMPONENTS log)
add_subdirectory(${PROJECT_SOURCE_DIR}/libs/glsl-optimizer)
find_package(Lua51)

add_subdirectory(src/gxm)

add_subdirectory(examples)


