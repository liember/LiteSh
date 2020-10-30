cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(liteSH CXX)
include_directories(src)

add_subdirectory(lib/googletest)
add_subdirectory(src)
add_subdirectory(tests)




