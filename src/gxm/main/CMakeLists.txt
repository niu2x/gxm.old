add_library(gxm_main "")

target_include_directories(gxm_main PUBLIC 
	${PROJECT_SOURCE_DIR}/src)

target_sources(gxm_main PRIVATE 
	app.cpp)

