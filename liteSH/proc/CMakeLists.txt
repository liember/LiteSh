project(proc)				
set(SOURCE_LIB procs.cpp )
include_directories(${EXEPTIONS})
add_library(proc STATIC ${SOURCE_LIB})