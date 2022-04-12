cmake_minimum_required(VERSION 3.21)

project(cpp_learn)

# os check
if (CMAKE_HOST_WIN32)
    set(WINDOWS 1)
elseif (CMAKE_HOST_APPLE)
    set(MACOS 1)
elseif (CMAKE_HOST_UNIX)
    set(LINUX 1)
endif ()

set(CMAKE_CXX_STANDARD 17)

if (MACOS)
    set(BOOST_ROOT "/usr/local/include/boost")
    include_directories(/usr/local/include) # header files searching path
    link_directories(/usr/local/lib) # library files searching path
elseif (WINDOWS)
    set(BOOST_ROOT " E:\\libs\\boost_1_78_0")
    include_directories(${BOOST_ROOT}) # header files searching path
    link_directories(${BOOST_ROOT}\\stage\\lib) # library files searching path

    #elseif (LINUX)
    #    message("配置LINUX VCPKG 路径")
    #    include_directories(/home/dev/Desktop/vcpkg/installed/x64-linux/include)
    #    link_directories(/home/dev/Desktop/vcpkg/installed/x64-linux/lib)
endif ()

add_executable(cpp_learn main.cpp)
