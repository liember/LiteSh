
project(Server CXX)

set(SOURCES Server.cpp)

find_package (Threads REQUIRED)
add_executable(Server ${SOURCES})

target_include_directories(liteSH PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries (Server ${CMAKE_THREAD_LIBS_INIT})

