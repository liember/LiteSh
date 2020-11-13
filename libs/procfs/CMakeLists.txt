
project(procfs)				
set(SOURCE_LIB procfs.cpp procfs.hpp)
include_directories(${LIBS})
add_library(procfs STATIC ${SOURCE_LIB})
target_include_directories(procfs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )