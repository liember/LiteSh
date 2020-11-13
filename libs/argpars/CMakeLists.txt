
project(argpars)				
set(SOURCE_LIB arprs.cpp argsParser.hpp)
include_directories(${EXEPTIONS})
add_library(argpars STATIC ${SOURCE_LIB})
target_include_directories(argpars PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )