
project(argpars)				
set(SOURCE_LIB arprs.cpp argpars.hpp)
include_directories(${EXEPTIONS})
add_library(argpars STATIC ${SOURCE_LIB})