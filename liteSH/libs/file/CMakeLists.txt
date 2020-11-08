
project(file_lsh)				
set(SOURCE_LIB file.cpp file.hpp )
include_directories(${LIBS})
add_library(file_lsh STATIC ${SOURCE_LIB})
target_include_directories(file_lsh PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
