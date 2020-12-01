
project(file)		

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")

set(SOURCE_LIB file.cpp file.hpp )
add_library(file STATIC ${SOURCE_LIB})
target_include_directories(file PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${LIBS})
