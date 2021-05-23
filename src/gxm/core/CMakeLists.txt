add_library(gxm_core "")

target_include_directories(gxm_core PUBLIC 
	${PROJECT_SOURCE_DIR}/src)

target_sources(gxm_core PRIVATE 
	object.cpp
)

