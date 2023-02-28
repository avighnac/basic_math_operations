cmake_minimum_required(VERSION 3.16)
set (CMAKE_CXX_STANDARD 17)

project(basic_math_operations C)

option(ENABLE_TESTS "Build tests" OFF)
option(BENCHMARK "Benchmark" OFF)

add_subdirectory(src/library)

if (ENABLE_TESTS)
    add_subdirectory(src/tests)
endif()

if (BENCHMARK)
    add_subdirectory(src/benchmark)
endif()
