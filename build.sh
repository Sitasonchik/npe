#!/bin/bash
rm -rf build
mkdir build
cd build
cmake ..
make
cp ../test.txt .
