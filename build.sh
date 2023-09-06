# to allow execution: chmod +x build.sh
# to run: ./build


#!/bin/bash
# Bash file to build the project

# Create build directory
mkdir -p build

# Go to build directory
cd build

# Run cmake
cmake ..

# Run make
make

# Run tests
#ctest

# Run the programs that start in "test-"
./test_*