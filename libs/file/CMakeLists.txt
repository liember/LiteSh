
project(file)				
set(SOURCE_LIB file.cpp file.hpp )
include_directories(${LIBS})
include_directories(${EXEPTIONS})
add_library(file STATIC ${SOURCE_LIB})