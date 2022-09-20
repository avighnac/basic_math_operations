project(basic_math_operations C)

option(ENABLE_TESTS "Build tests" OFF)

add_subdirectory(src/library)

if(ENABLE_TESTS)
    add_subdirectory(src/tests)
endif()