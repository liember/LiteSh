
project(liteSH CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(SOURCES main.cpp argexec.cpp argexec.hpp sighandl.hpp dlload.h)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/man.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(liteSH ${SOURCES})
add_subdirectory(shell)

add_subdirectory(dynlib)
add_subdirectory(server)

target_include_directories(liteSH PUBLIC ${LIBS})
target_include_directories(liteSH PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(liteSH shell)
target_link_libraries(liteSH argpars)
target_link_libraries(liteSH server)

target_link_libraries(liteSH ${CMAKE_DL_LIBS})

