add_executable(mytest src/test.cc)
target_link_libraries(mytest PUBLIC GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main hello_interface)
