cmake_minimum_required(VERSION 3.16)
project(cpp_learn)

set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

find_path(DBG_MACRO_INCLUDE_DIRS "dbg.h")

add_executable(0_demo 0_demo.cc)
add_executable(1_features 1_features.cc)

target_include_directories(0_demo PRIVATE ${DBG_MACRO_INCLUDE_DIRS})
target_include_directories(1_features PRIVATE ${DBG_MACRO_INCLUDE_DIRS})
