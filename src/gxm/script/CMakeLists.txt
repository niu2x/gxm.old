add_library(gxm_script "")

target_include_directories(gxm_script PUBLIC 
	${PROJECT_SOURCE_DIR}/src
	${LUA_INCLUDE_DIR}
)

target_sources(gxm_script PRIVATE 
	lua_engine.cpp
)

target_link_libraries(gxm_script PRIVATE 
	${LUA_LIBRARIES}
    ${CMAKE_DL_LIBS}
)

