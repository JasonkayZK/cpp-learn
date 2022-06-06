cmake_minimum_required(VERSION 3.16)

ENABLE_LANGUAGE(ASM)

SET(STACK_CO_SOURCE_FILES
        switch_context.S
        context.cc
        context.h
        coroutine.cc
        coroutine.h
        environment.cc
        environment.h
        status.h
        utils.h)

add_executable(stack_co_test stack_co_test.cc ${STACK_CO_SOURCE_FILES})
