project(cmd)				
set(SOURCE_LIB procs.cpp )

add_library(proc STATIC ${SOURCE_LIB})
target_include_directories(cmd PUBLIC ${LIBS})