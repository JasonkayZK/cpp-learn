cmake_minimum_required(VERSION 3.16)
project(cpp_learn)

set(CMAKE_CXX_STANDARD 11)

add_executable(person person.cpp)

add_executable(mutex_test mutex.cpp test_mutex_lock.cpp)