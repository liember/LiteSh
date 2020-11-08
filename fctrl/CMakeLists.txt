
project(fctrl CXX)

set(LIBS ${CMAKE_CURRENT_SOURCE_DIR}/libs)
set(SOURCES main.cpp argexec.hpp argexec.cpp)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/man.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(${LIBS}/file)
add_subdirectory(${LIBS}/procfs)
add_subdirectory(${LIBS}/argpars)        

add_executable(fctrl ${SOURCES})

target_link_libraries(fctrl PRIVATE file)
target_link_libraries(fctrl PRIVATE procfs)
target_link_libraries(fctrl PRIVATE argpars)

target_include_directories(fctrl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} )
target_include_directories(fctrl PRIVATE ${LIBS})