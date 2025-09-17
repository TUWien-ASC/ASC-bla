cmake_minimum_required(VERSION 3.20)
project(ASC_bla)

set (CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable (demo_vector demos/demo_vector.cpp)
target_sources (demo_vector PUBLIC src/vector.hpp src/expression.hpp)





