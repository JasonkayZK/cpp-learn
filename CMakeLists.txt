cmake_minimum_required(VERSION 3.16)
project(aotpp_demo)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES src/main.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

set(TEST_SOURCE_FILES test/tests.cc)
set(TEST_EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

find_package(oatpp CONFIG REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE oatpp::oatpp oatpp::oatpp-test)

add_executable(${PROJECT_NAME}_test ${TEST_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}_test PRIVATE oatpp::oatpp oatpp::oatpp-test)
