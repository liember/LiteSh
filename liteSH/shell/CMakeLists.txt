project(shell)
set(SOURCE_LIB proc.hpp shell.cpp shell.hpp)
add_library(shell STATIC ${SOURCE_LIB})

target_include_directories(shell PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(shell PUBLIC ${LIBS})

target_link_libraries(shell cmdline)
target_link_libraries(shell procfs)
target_link_libraries(shell file)