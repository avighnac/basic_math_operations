project(tests CXX)

enable_language(CXX)

add_executable(tests test.cpp)

target_link_libraries(tests basic_math_operations)

target_include_directories(tests PRIVATE "../library")