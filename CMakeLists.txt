project(basic_math_operations C)

option(ENABLE_TESTS "Build tests" ON)
option(BENCHMARK "Benchmark" OFF)

add_subdirectory(src/library)

if (ENABLE_TESTS)
    add_subdirectory(src/tests)
endif()

if (BENCHMARK)
    add_subdirectory(src/benchmark)
endif()