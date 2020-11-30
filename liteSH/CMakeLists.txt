
project(liteSH CXX)

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

