
project(file)				
set(SOURCE_LIB file.cpp )
include_directories(${LIBS})
include_directories(${EXEPTIONS})
add_library(file STATIC ${SOURCE_LIB})