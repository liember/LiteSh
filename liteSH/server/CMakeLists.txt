project(server)
set(SOURCE_LIB server.cpp server.hpp)
add_library(server STATIC ${SOURCE_LIB})

target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(server PUBLIC ${LIBS})

find_package(Boost 1.73.0 REQUIRED system)
target_link_libraries(server ${Boost_LIBRARIES} pthread)

target_link_libraries(server shell)
target_link_libraries(server procfs)
target_link_libraries(server file)