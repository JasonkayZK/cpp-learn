cmake_minimum_required(VERSION 3.16)

SET(STACK_CO_SOURCE_FILES
        environment.cc
        environment.h)

ADD_LIBRARY(stack_co ${STACK_CO_SOURCE_FILES})
