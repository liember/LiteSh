
project(fctrl CXX)

set(SOURCES main.cpp argexec.hpp)
add_executable(fctrl ${SOURCES})



add_subdirectory(${LIBS}/file file)
add_subdirectory(${LIBS}/argpars argpars)



target_link_libraries(fctrl file)
target_link_libraries(fctrl argpars)

include_directories(fctrl PUBLIC ./ )
include_directories(fctrl PUBLIC ${LIBS}/argpars )
include_directories(fctrl PUBLIC ${LIBS}/file )
include_directories(fctrl PUBLIC ${LIBS})