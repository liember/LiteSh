project(fctrl CXX)

set(SOURCES main.cpp argexec.hpp argexec.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/man.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(fctrl ${SOURCES})

target_include_directories(fctrl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} )
target_include_directories(liteSH PRIVATE ${LIBS} ${LIBS}/file ${LIBS}/argpars ${LIBS}/procfs)

target_link_libraries(fctrl PRIVATE file)
target_link_libraries(fctrl PRIVATE procfs)
target_link_libraries(fctrl PRIVATE argpars)
