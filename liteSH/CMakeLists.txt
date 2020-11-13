
project(liteSH CXX)

set(SOURCES src/main.cpp src/argexec.cpp src/argexec.hpp src/proc.hpp src/sighandl.hpp)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/man.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(liteSH ${SOURCES})

target_include_directories(liteSH PRIVATE ${LIBS})
target_include_directories(liteSH PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(liteSH argpars)
target_link_libraries(liteSH procfs)
target_link_libraries(liteSH file)

