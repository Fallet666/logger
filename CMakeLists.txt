cmake_minimum_required(VERSION 3.10)
project(logger)

set(CMAKE_CXX_STANDARD 17)

add_executable(logger
        main.cpp
)

enable_testing()
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/release-1.11.0.tar.gz
)
# Эта строка загружает и собирает Google Test
FetchContent_MakeAvailable(googletest)


add_executable(my_tests tests/my_tests.cpp)
target_link_libraries(my_tests gtest gtest_main)
add_test(NAME MyTests COMMAND my_tests)