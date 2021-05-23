add_executable(gxm "")
add_subdirectory(main)
add_subdirectory(render)
add_subdirectory(core)
add_subdirectory(script)

target_include_directories(gxm PUBLIC 
    ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(gxm PUBLIC 
    Threads::Threads
    # glsl_optimizer
    Boost::headers
    Boost::log
    gxm_main
    gxm_core
    gxm_render
    gxm_script
)

target_sources(gxm PRIVATE
    gxm.cpp
)


