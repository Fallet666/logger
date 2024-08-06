cmake_minimum_required(VERSION 3.10)
project(logger)

set(CMAKE_CXX_STANDARD 17)

set(DEFAULT_LOG_LEVEL DEBUG)
add_compile_definitions(GLOBAL_LOG_LEVEL=${DEFAULT_LOG_LEVEL})

include_directories(include)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/release-1.11.0.tar.gz
)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 9.1.0
        DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(fmt)

add_library(logger_lib
        src/logger/logger.cpp
)
target_link_libraries(logger_lib PRIVATE fmt::fmt)
target_include_directories(logger_lib PUBLIC ${fmt_SOURCE_DIR}/include)

set_target_properties(logger_lib PROPERTIES PUBLIC_HEADER include/logger/logger.h)

add_executable(logger
        main.cpp
)
target_link_libraries(logger PRIVATE logger_lib fmt::fmt)
target_include_directories(logger PRIVATE ${fmt_SOURCE_DIR}/include)

enable_testing()

add_executable(my_tests tests/tests.cpp)
target_link_libraries(my_tests PRIVATE logger_lib gtest gtest_main)
add_test(NAME Tests COMMAND my_tests)
