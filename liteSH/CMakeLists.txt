
project(liteSH CXX)

set(SOURCES main.cpp)

include_directories(${LIBS})
include_directories(sig)
include_directories(proc)

add_subdirectory(sig)
add_subdirectory(proc)

add_executable(liteSH ${SOURCES})

target_link_libraries(liteSH sig)
target_link_libraries(liteSH proc)
