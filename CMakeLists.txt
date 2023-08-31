cmake_minimum_required(VERSION 3.20)
project(ASC_bla)

set (CMAKE_CXX_STANDARD 17)

include_directories(src)

# add_executable (test_vector tests/test_vector.cc)


# recommended from pybind:
# find_package(Python 3.6 COMPONENTS Interpreter Development REQUIRED)
# find_package(pybind11 CONFIG REQUIRED)



find_package(Python 3.8 COMPONENTS Interpreter Development.Module REQUIRED)

execute_process(
  COMMAND "${Python_EXECUTABLE}" -m pybind11 --cmakedir
  OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE PYBIND11_DIR)
list(APPEND CMAKE_PREFIX_PATH "${PYBIND11_DIR}")
find_package(pybind11 CONFIG REQUIRED)


pybind11_add_module(ASC_bla src/pybind.cpp)

# not working:
# install (TARGETS ASC_bla)

