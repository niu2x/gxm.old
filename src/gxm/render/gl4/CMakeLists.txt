add_library(gxm_gl4_render "")

target_include_directories(gxm_gl4_render PUBLIC 
    ${PROJECT_SOURCE_DIR}/src)

target_sources(gxm_gl4_render PRIVATE
	render.cpp
	window.cpp
)

target_link_libraries(gxm_gl4_render PRIVATE
    gxm_render
    GLEW::GLEW
    glfw
    OpenGL::OpenGL
)