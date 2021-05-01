cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)

project(GXM VERSION 0.1.0 LANGUAGES CXX C)

add_executable(gxm "")

find_package(glfw3)
target_link_libraries(gxm PRIVATE glfw)

find_package(OpenGL)
target_link_libraries(gxm PRIVATE OpenGL::OpenGL)

find_package(Threads)
target_link_libraries(gxm PRIVATE Threads::Threads)

message(STATUS "Boost_FIND_COMPONENTS ${Boost_FIND_COMPONENTS}")

find_package(Boost COMPONENTS log)
target_link_libraries(gxm PRIVATE 
	Boost::headers
	Boost::log
)

target_sources(gxm PRIVATE 
	src/main.cpp
)