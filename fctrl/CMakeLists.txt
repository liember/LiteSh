
project(fctrl CXX)

set(INCLUDE ${CMAKE_SOURCE_DIR}/fctrl/include)
include_directories(${INCLUDE})

set(SOURCES main.cpp)
add_executable(fctrl ${SOURCES})

add_subdirectory(file)
include_directories(file)
target_link_libraries(fctrl file)

add_subdirectory(argpars)
include_directories(argpars)
target_link_libraries(fctrl argpars)


