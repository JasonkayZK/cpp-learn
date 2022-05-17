cmake_minimum_required(VERSION 3.5.1)

# OS Settings
if (CMAKE_HOST_WIN32)
    message("WinOS Config")
    set(WINDOWS 1)
elseif (CMAKE_HOST_APPLE)
    message("MacOS Config")
    set(MACOS 1)
elseif (CMAKE_HOST_UNIX)
    message("Linux Config")
    set(LINUX 1)
endif ()

if (MACOS)
    set(CMAKE_TOOLCHAIN_FILE "/Users/Kylinkzhang/vcpkg/scripts/buildsystems/vcpkg.cmake")
elseif (WINDOWS)
    set(CMAKE_TOOLCHAIN_FILE "E:/vcpkg/scripts/buildsystems/vcpkg.cmake")
ELSEIF(LINUX)
    set(CMAKE_TOOLCHAIN_FILE "/root/self-workspace/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif ()

project(HelloWorld C CXX)

include(cmake/common.cmake)

# Proto file
get_filename_component(hw_proto "proto/helloworld.proto" ABSOLUTE)
get_filename_component(hw_proto_path "${hw_proto}" PATH)

# Generated sources
set(hw_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/helloworld.pb.cc")
set(hw_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/helloworld.pb.h")
set(hw_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/helloworld.grpc.pb.cc")
set(hw_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/helloworld.grpc.pb.h")
add_custom_command(
        OUTPUT "${hw_proto_srcs}" "${hw_proto_hdrs}" "${hw_grpc_srcs}" "${hw_grpc_hdrs}"
        COMMAND ${_PROTOBUF_PROTOC}
        ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${hw_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${hw_proto}"
        DEPENDS "${hw_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# hw_grpc_proto
add_library(hw_grpc_proto
        ${hw_grpc_srcs}
        ${hw_grpc_hdrs}
        ${hw_proto_srcs}
        ${hw_proto_hdrs})
target_link_libraries(hw_grpc_proto
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF})

# Targets greeter_[async_](client|server)
foreach (_target
        greeter_client greeter_server
        greeter_callback_client greeter_callback_server
        greeter_async_client greeter_async_client2 greeter_async_server)
    add_executable(${_target} "${_target}.cc")
    target_link_libraries(${_target}
            hw_grpc_proto
            ${_REFLECTION}
            ${_GRPC_GRPCPP}
            ${_PROTOBUF_LIBPROTOBUF})
endforeach ()
