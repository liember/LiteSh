
project(fctrl CXX)

set(SOURCES main.cpp)

include_directories(${LIBS}/file ${LIBS}/argpars ${LIBS})

add_subdirectory(${LIBS}/file file)
add_subdirectory(${LIBS}/argpars argpars)

add_executable(fctrl ${SOURCES})

target_link_libraries(fctrl file)
target_link_libraries(fctrl argpars)


