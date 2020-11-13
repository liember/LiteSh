project(test)
add_executable(
        unit_tests
        file.cpp
        main.cpp
)

add_subdirectory(googletest)

target_include_directories(
        unit_tests
        PRIVATE
        ${LIBS}
)
target_link_libraries(
        unit_tests
        gtest_main
        file
)

