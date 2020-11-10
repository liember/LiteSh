
project(liteSH CXX)

set(LIBS ${CMAKE_CURRENT_SOURCE_DIR}/libs)
set(SOURCES main.cpp argexec.cpp argexec.hpp proc.hpp sighandl.hpp)

add_subdirectory(${LIBS}/argpars)
add_subdirectory(${LIBS}/procfs)
add_subdirectory(${LIBS}/file)

add_executable(liteSH ${SOURCES})

target_include_directories(liteSH PRIVATE ${LIBS})
target_include_directories(liteSH PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(liteSH argpars_lsh)
target_link_libraries(liteSH procfs_lsh)
target_link_libraries(liteSH file_lsh)

