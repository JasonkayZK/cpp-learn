cmake_minimum_required(VERSION 3.16)

SET(STACKLESS_CO_SOURCE_FILES
        coroutine.cc
        coroutine.h
        schedule.cc
        schedule.h)

add_executable(stackless_co_test stackless_co_test.cc ${STACKLESS_CO_SOURCE_FILES})
