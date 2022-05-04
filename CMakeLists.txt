cmake_minimum_required(VERSION 3.16)
project(fmt_learn)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpp_learn main.cpp)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(cpp_learn PRIVATE fmt::fmt)