add_library(gxm_render "")
add_subdirectory(gl4)

target_include_directories(gxm_render PUBLIC 
    ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(gxm_render PRIVATE
    gxm_gl4_render
)

target_sources(gxm_render PRIVATE 
	render.cpp
	window.cpp
)

