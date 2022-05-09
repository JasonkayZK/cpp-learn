cmake_minimum_required(VERSION 3.16)
project(cpp_learn)

set(CMAKE_CXX_STANDARD 20)


add_executable(0_copy_semantics 0_copy_semantics.cc)
add_executable(1_move_semantics 1_move_semantics.cc)
add_executable(1p_move_semantics 1_move_and_destructor.cc)
add_executable(2_forward 2_forward.cc)
