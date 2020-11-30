project(dynlib)
set(SOURCE_LIB dynlib.c)
add_library(dynlib SHARED ${SOURCE_LIB})
target_include_directories(dynlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})