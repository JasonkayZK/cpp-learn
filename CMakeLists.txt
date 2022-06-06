cmake_minimum_required(VERSION 3.16)

# Set environment
set(REMOTE_DEV_MODE TRUE)

# Ignore error for cross-compiling
if (REMOTE_DEV_MODE)
    set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
    SET(CMAKE_BUILD_TYPE DEBUG)
endif ()

project(coroutine)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpp_20_demo cpp20_demo/cpp_20_demo.cc)

TARGET_LINK_LIBRARIES(cpp_20_demo stack_co)
