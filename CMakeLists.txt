cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

project(basic_math_operations C)

option(ENABLE_TESTS "Build tests" OFF)
option(BENCHMARK "Benchmark" ON)
option(
  BMO_BIG_TEST_FILES
  "Clone the big test files from github (only use this if you really wanna check that nothing's wrong)"
  OFF)

add_subdirectory(src/library)

if(BMO_BIG_TEST_FILES)
    include(FetchContent)

    message(STATUS "Fetching basic_math_operations_tests...")
    FetchContent_Declare(bmo_tests
        GIT_REPOSITORY https://github.com/avighnac/basic_math_operations_tests
        GIT_TAG main
    )
    FetchContent_GetProperties(bmo_tests)
    if(NOT bmo_tests_POPULATED)
        message(STATUS "Populating basic_math_operations_tests...")
        FetchContent_Populate(bmo_tests)
    endif()
endif()

if(ENABLE_TESTS)
  add_subdirectory(src/tests)
endif()

if(BENCHMARK)
  add_subdirectory(src/benchmark)
endif()
