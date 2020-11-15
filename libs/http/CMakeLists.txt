
project(http)
set(SOURCE_LIB client.cpp client.hpp)
include_directories(${LIBS})
add_library(http STATIC ${SOURCE_LIB})
target_include_directories(http PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )