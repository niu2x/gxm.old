add_library(gxm "")
add_subdirectory(main)
add_subdirectory(render)

target_include_directories(gxm PUBLIC 
    ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(gxm PUBLIC 
    Threads::Threads
    # glsl_optimizer
    Boost::headers
    Boost::log
    gxm_main
    gxm_render
)

target_sources(gxm PRIVATE
    gxm.cpp
)


