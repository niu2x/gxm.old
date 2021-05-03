cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)

project(GXM VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_library(gxm "")

find_package(glfw3)
target_link_libraries(gxm PUBLIC glfw)

find_package(OpenGL)
target_link_libraries(gxm PUBLIC OpenGL::OpenGL)

find_package(GLEW)
target_link_libraries(gxm PUBLIC GLEW::GLEW)

find_package(Threads)
target_link_libraries(gxm PUBLIC Threads::Threads)

add_subdirectory(libs/glsl-optimizer)
target_link_libraries(gxm PUBLIC glsl_optimizer)


message(STATUS "Boost_FIND_COMPONENTS ${Boost_FIND_COMPONENTS}")

find_package(Boost COMPONENTS log)
target_link_libraries(gxm PUBLIC 
	Boost::headers
	Boost::log
)

if(MSVC)
  target_compile_options(gxm PRIVATE /W4 /WX)
else()
  target_compile_options(gxm PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

target_include_directories(gxm PUBLIC src)
target_include_directories(gxm PUBLIC libs/)

target_sources(gxm PRIVATE 
	# src/main.cpp
	src/gxm/gl_renderbuffer.cpp
	src/gxm/gl_buffer.cpp
	src/gxm/gl_context.cpp
	src/gxm/gl_draw_command.cpp
	src/gxm/gl_blend.cpp
	src/gxm/gl_program.cpp
	src/gxm/gl_draw_polygon.cpp
	src/gxm/gl_texture.cpp
	src/gxm/gl_vertex.cpp
	src/gxm/gl_framebuffer.cpp
	src/gxm/gl_vertex_array.cpp
	src/gxm/exception.cpp
	src/gxm/geometry.cpp
	src/gxm/log.cpp
	src/gxm/app.cpp
	src/gxm/glsl.cpp
)


add_executable(empty_window "examples/empty_window.cpp")
target_link_libraries(empty_window PRIVATE gxm)

add_executable(triangle "examples/triangle.cpp")
target_link_libraries(triangle PRIVATE gxm)

add_executable(srgb "examples/srgb.cpp")
target_link_libraries(srgb PRIVATE gxm)

add_executable(texture "examples/texture.cpp")
target_link_libraries(texture PRIVATE gxm)

add_executable(framebuffer "examples/framebuffer.cpp")
target_link_libraries(framebuffer PRIVATE gxm)