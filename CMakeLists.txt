cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)

project(GXM VERSION 0.1.0 LANGUAGES CXX C)

add_library(gxm "")

find_package(glfw3)
target_link_libraries(gxm PRIVATE glfw)

find_package(OpenGL)
target_link_libraries(gxm PRIVATE OpenGL::OpenGL)

find_package(GLEW)
target_link_libraries(gxm PRIVATE GLEW::GLEW)

find_package(Threads)
target_link_libraries(gxm PRIVATE Threads::Threads)

message(STATUS "Boost_FIND_COMPONENTS ${Boost_FIND_COMPONENTS}")

find_package(Boost COMPONENTS log)
target_link_libraries(gxm PRIVATE 
	Boost::headers
	Boost::log
)

if(MSVC)
  target_compile_options(gxm PRIVATE /W4 /WX)
else()
  target_compile_options(gxm PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

target_include_directories(gxm PUBLIC src)

target_sources(gxm PRIVATE 
	# src/main.cpp
	src/gxm/texture.cpp
	src/gxm/gl_buffer.cpp
	src/gxm/gl_context.cpp
	src/gxm/exception.cpp
	src/gxm/app.cpp
)


add_executable(empty_window "examples/empty_window.cpp")
target_link_libraries(empty_window PRIVATE gxm)