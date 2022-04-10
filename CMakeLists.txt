cmake_minimum_required(VERSION 3.21)

project(cpp_learn)

set(CMAKE_CXX_STANDARD 17)

set(BOOST_ROOT "/usr/local/include/boost")

include_directories(/usr/local/include) # header files searching path

link_directories(/usr/local/lib) # library files searching path

add_executable(cpp_learn main.cpp)