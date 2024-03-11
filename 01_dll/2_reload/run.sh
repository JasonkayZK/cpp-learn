#!/bin/bash
set -e # stop the script on errors

g++ -fPIC -shared -o libhello.so hello.cc -std=c++17
g++ -o main main.cc -ldl -std=c++17
./main
