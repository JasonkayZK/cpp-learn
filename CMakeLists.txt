cmake_minimum_required(VERSION 3.16)
project(cpp_learn)

set(CMAKE_CXX_STANDARD 20)

add_executable(main main.cc)

find_package(GTest CONFIG REQUIRED)
target_link_libraries(main PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)
