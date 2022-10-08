project(benchmark CXX)

enable_language(CXX)

add_executable(benchmark benchmark.cpp)

target_link_libraries(benchmark basic_math_operations)

target_include_directories(benchmark PRIVATE "../library")