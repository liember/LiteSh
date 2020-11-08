
project(argpars_lsh)				
set(SOURCE_LIB arprs.cpp argpars.hpp)
include_directories(${EXEPTIONS})
add_library(argpars_lsh STATIC ${SOURCE_LIB})
target_include_directories(argpars_lsh PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )