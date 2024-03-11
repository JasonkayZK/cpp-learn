#!/bin/bash
set -e # stop the script on errors

g++ -fPIC -shared -o libhello.so hello.cc
g++ -o main main.cc -ldl
./main
