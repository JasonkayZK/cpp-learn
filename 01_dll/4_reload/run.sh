#!/bin/bash
set -e # stop the script on errors

cmake -B build
cmake --build build
./build/test/mytest
