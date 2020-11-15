cmake_minimum_required(VERSION 3.10)

project(AWS CXX)

set(LIBS ${CMAKE_CURRENT_SOURCE_DIR}/libs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(${LIBS}/argpars)
add_subdirectory(${LIBS}/file)
add_subdirectory(${LIBS}/procfs)
add_subdirectory(${LIBS}/http)

add_subdirectory(liteSH)
add_subdirectory(fctrl)
add_subdirectory(Server)

add_subdirectory(test)





