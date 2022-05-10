#include <iostream>
#include "gtest/gtest.h"

TEST(HelloTest, PrintHello) {
    std::string str{"Hello, World!"};
    ASSERT_EQ(str, "Hello, World!");
    ASSERT_EQ(str.size(), 13);
}

class VectorTest : public ::testing::Test {
protected:
    // set resources before test
    void SetUp() override {
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
    }

    // clean up resources after test
    void TearDown() override {
        vec.clear();
    }

    std::vector<int> vec;
};

// Here we are using TEST_F, not TEST
TEST_F(VectorTest, PushBack) {
    // We changed vec here, but this is invisible to other test cases
    vec.push_back(4);
    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec.back(), 4);
}

TEST_F(VectorTest, Size) {
    ASSERT_EQ(vec.size(), 3);
}

int main(int argc, char **argv) {
    printf("Running main() from %s\n", __FILE__);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
