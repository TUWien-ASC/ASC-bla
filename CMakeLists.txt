cmake_minimum_required(VERSION 3.20)
project(ASC_bla)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

include_directories(src)

add_executable (test_vector tests/test_vector.cc)
add_executable(test_matrix tests/test_matrix.cc)

add_test(NAME test_vector COMMAND test_vector)
add_test(NAME test_matrix COMMAND test_matrix)


