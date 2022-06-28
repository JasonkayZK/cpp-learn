include_directories(${PROJECT_SOURCE_DIR}/my-tiny-stl)

# stl test
set(APP_SRC main.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(stltest ${APP_SRC})

# stl utils test
set(TEST_UTILS FALSE)

if ("${TEST_UTILS}" STREQUAL "TRUE")
    set(APP_UTILS_SRC utils/main.cc)
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/test/bin)

    add_executable(stl_util_test ${APP_UTILS_SRC})

    # dependencies
    find_package(GTest CONFIG REQUIRED)
    target_link_libraries(stl_util_test PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)
endif ()
