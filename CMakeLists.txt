cmake_minimum_required(VERSION 3.10)
project(logger)

set(CMAKE_CXX_STANDARD 17)

include_directories(include/logger)

add_executable(logger
        main.cpp
        src/logger/logger.cpp
        include/logger/logger.h
)

enable_testing()
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/release-1.11.0.tar.gz
)
# Эта строка загружает и собирает Google Test
FetchContent_MakeAvailable(googletest)

find_package(fmt REQUIRED)
target_link_libraries(logger PRIVATE fmt::fmt)


add_executable(my_tests tests/my_tests.cpp)
target_link_libraries(my_tests gtest gtest_main)
add_test(NAME MyTests COMMAND my_tests)