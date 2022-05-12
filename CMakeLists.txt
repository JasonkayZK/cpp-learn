cmake_minimum_required(VERSION 3.16)
project(cpp_learn)

set(CMAKE_CXX_STANDARD 20)

add_executable(rvo rvo.cc)
add_executable(nrvo nrvo.cc)
add_executable(nrvo_2 nrvo_2.cc)
add_executable(nrvo_with_exception nrvo_with_exception.cc)
add_executable(nrvo_different_name nrvo_different_name.cc)
add_executable(nrvo_side_effects nrvo_side_effects.cc)
