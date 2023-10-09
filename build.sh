# to allow execution: chmod +x build.sh
# to run: ./build.sh


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

# Run all the programs that start in "test_*" in the build directory that are executables
find . -name "test_*" -type f -exec {} \;


