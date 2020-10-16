cmake_minimum_required(VERSION 3.0)

project(fsctrl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(lab2 fctrl.cpp)
target_link_libraries(lab2)


