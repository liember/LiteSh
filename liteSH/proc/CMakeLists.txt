project(proc)				
set(SOURCE_LIB procs.cpp )

add_library(proc STATIC ${SOURCE_LIB})
target_include_directories(proc PUBLIC ${LIBS})