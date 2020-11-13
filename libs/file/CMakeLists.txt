
project(file)				
set(SOURCE_LIB file.cpp file.hpp )
include_directories(${LIBS})
add_library(file STATIC ${SOURCE_LIB})
target_include_directories(file PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
