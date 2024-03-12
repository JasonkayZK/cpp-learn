project(4_reload LANGUAGES CXX)

cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif ()

add_subdirectory(reload)
add_subdirectory(main)
add_subdirectory(hello)

find_package(GTest CONFIG REQUIRED)
enable_testing()
add_subdirectory(test)
