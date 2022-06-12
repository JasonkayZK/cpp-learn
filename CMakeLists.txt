cmake_minimum_required(VERSION 3.16)

# Set environment
set(REMOTE_DEV_MODE TRUE)

# Ignore error for cross-compiling
if (REMOTE_DEV_MODE)
    set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
    SET(CMAKE_BUILD_TYPE DEBUG)
endif ()

project(coroutine)

ADD_SUBDIRECTORY(cpp20_demo)

ADD_SUBDIRECTORY(setjmp_demo)

ADD_SUBDIRECTORY(stack_co)

ADD_SUBDIRECTORY(stackless_co)

set(CMAKE_CXX_STANDARD 20)
