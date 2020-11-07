
project(fctrl CXX)

set(SOURCES main.cpp argexec.hpp argexec.cpp)
add_executable(fctrl ${SOURCES})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/man.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(${LIBS}/file ${CMAKE_CURRENT_BINARY_DIR}/file EXCLUDE_FROM_ALL)
add_subdirectory(${LIBS}/procfs ${CMAKE_CURRENT_BINARY_DIR}/procfs EXCLUDE_FROM_ALL)
add_subdirectory(${LIBS}/argpars ${CMAKE_CURRENT_BINARY_DIR}/argpars EXCLUDE_FROM_ALL)

target_link_libraries(fctrl PRIVATE file)
target_link_libraries(fctrl PRIVATE procfs)
target_link_libraries(fctrl PRIVATE argpars)

target_include_directories(fctrl PRIVATE ./ )
target_include_directories(fctrl PRIVATE ${LIBS}/argpars )
target_include_directories(fctrl PRIVATE ${LIBS}/file )
target_include_directories(fctrl PRIVATE ${LIBS}/procfs )
target_include_directories(fctrl PRIVATE ${LIBS})