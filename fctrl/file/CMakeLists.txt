
project(file)				
set(SOURCE_LIB fctrl.cpp )
include_directories(${EXEPTIONS})
add_library(file STATIC ${SOURCE_LIB})