
project(fctrl CXX)

set(INCLUDE ${CMAKE_SOURCE_DIR}/fctrl/include)
include_directories(${INCLUDE})

set(SOURCES main.cpp)
add_executable(fctrl ${SOURCES})
