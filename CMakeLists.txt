cmake_minimum_required(VERSION 3.16)
project(aotpp_demo)

set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(main main.cc)

find_package(oatpp CONFIG REQUIRED)
target_link_libraries(main PRIVATE oatpp::oatpp oatpp::oatpp-test)
