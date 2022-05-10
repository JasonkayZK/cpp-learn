cmake_minimum_required(VERSION 3.16)
project(cpp_learn)

set(CMAKE_CXX_STANDARD 20)

add_executable(main_test main_test.cc)

find_package(GTest CONFIG REQUIRED)
target_link_libraries(main_test PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)
