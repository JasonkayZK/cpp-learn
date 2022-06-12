cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)

SET(STACKLESS_CO_SOURCE_FILES
        utils.h
        coroutine.cc
        coroutine.h
        schedule.cc
        schedule.h)

add_executable(stackless_co_test stackless_co_test.cc ${STACKLESS_CO_SOURCE_FILES})
