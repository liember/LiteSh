
project(liteSH CXX)

set(INCLUDE ${CMAKE_SOURCE_DIR}/liteSH/include)
include_directories(${INCLUDE})

set(SOURCES main.cpp)
add_executable(liteSH ${SOURCES})

add_subdirectory(sig)
include_directories(sig)
target_link_libraries(liteSH sig)

add_subdirectory(proc)
include_directories(proc)
target_link_libraries(liteSH proc)

#add_subdirectory(cmd)
#include_directories(cmd)
#target_link_libraries(liteSH cmd)
