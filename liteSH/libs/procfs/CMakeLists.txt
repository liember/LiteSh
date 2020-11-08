
project(procfs_lsh)				
set(SOURCE_LIB procfs.cpp procfs.hpp)
include_directories(${LIBS})
add_library(procfs_lsh STATIC ${SOURCE_LIB})
target_include_directories(procfs_lsh PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )