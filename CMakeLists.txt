cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 11)

project(cpp_learn)

# os check
if (CMAKE_HOST_WIN32)
  set(WINDOWS 1)
  message("On Windows")
elseif (CMAKE_HOST_APPLE)
  set(MACOS 1)
  message("On MacOS")
elseif (CMAKE_HOST_UNIX)
  set(LINUX 1)
  message("On Linux")
endif ()

# Boost lib settings
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)

find_package(Boost REQUIRED)
if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif ()

add_subdirectory(000_version)
add_subdirectory(001_asio)
