cmake_minimum_required(VERSION 3.16)
project(dll_learn)

set(CMAKE_CXX_STANDARD 20)

ADD_SUBDIRECTORY(lib)

add_executable(run_dll run_dll.cpp)
