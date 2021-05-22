add_executable(empty_window "")
target_sources(empty_window PRIVATE "empty_window.cpp")
target_link_libraries(empty_window PRIVATE gxm)