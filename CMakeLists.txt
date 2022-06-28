cmake_minimum_required(VERSION 3.16)
project(MyTinySTL)

set(CMAKE_CXX_STANDARD 20)

# project version
set(MyTinySTL_VERSION_MAJOR 1)
set(MyTinySTL_VERSION_MINOR 0)
set(MyTinySTL_VERSION_PATCH 0)
set(MyTinySTL_VERSION "${MyTinySTL_VERSION_MAJOR}.${MyTinySTL_VERSION_MINOR}.${MyTinySTL_VERSION_PATCH}")
message(STATUS "The version of this project is: ${MyTinySTL_VERSION}")

# build type
#set(CMAKE_BUILD_TYPE release)
set(CMAKE_BUILD_TYPE debug)

# build type
set(CMAKE_BUILD_TYPE release)

# compiler config
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -Wno-sign-compare -Wno-unused-but-set-variable -Wno-array-bounds")
    # set(EXTRA_CXX_FLAGS -Weffc++ -Wswitch-default -Wfloat-equal -Wconversion -Wsign-conversion)
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "5.0.0")
        message(FATAL_ERROR "required GCC 5.0 or later")
    else ()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif ()
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -Wno-sign-compare")
    # set(EXTRA_CXX_FLAGS -Weffc++ -Wswitch-default -Wfloat-equal -Wconversion -Wimplicit-fallthrough)
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "3.5.0")
        message(FATAL_ERROR "required Clang 3.5 or later")
    else ()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif ()
endif ()
message(STATUS "The cmake_cxx_flags is: ${CMAKE_CXX_FLAGS}")

# sub-project
add_subdirectory(${PROJECT_SOURCE_DIR}/test)
