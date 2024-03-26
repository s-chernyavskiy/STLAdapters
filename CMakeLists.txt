cmake_minimum_required(VERSION 3.22)
project(labwork9)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)
add_subdirectory(bin)

enable_testing()
add_subdirectory(tests)