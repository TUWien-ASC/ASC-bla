#!/bin/zsh

mydir=${0:a:h}
DIR="${mydir}/build/"

if [ ! -d "$DIR" ]; then
    mkdir -p $DIR 
    echo "Creating new build directory ${DIR}..."
fi

cd $DIR
cmake ..
make 