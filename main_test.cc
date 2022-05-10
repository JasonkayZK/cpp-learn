#include <iostream>
#include "gtest/gtest.h"

TEST(HelloTest, PrintHello) {
    std::string str{"Hello, World!"};
    ASSERT_EQ(str, "Hello, World!");
    ASSERT_EQ(str.size(), 13);
}

TEST(ExpectAndAssert, ExpectTest) {
    auto add = [](const int x, const int y) { return x + y; };

    EXPECT_EQ(add(1, 2), 4);
    EXPECT_EQ(add(1, 2), 3);
}

TEST(ExpectAndAssert, AssertTest) {
    auto subtract = [](const int x, const int y) { return x - y; };

//    ASSERT_EQ(subtract(3, 1), 3);
    ASSERT_EQ(subtract(3, 1), 2);
}


TEST(TestMessage, Message) {
    int result = 4;
    EXPECT_EQ(1 + 2, result) << "1+2 should equals to: " << result;
}

class GlobalEvent : public testing::Environment {
public:

    void SetUp() override {
        std::cout << "Before any case, Global" << std::endl;
    }

    void TearDown() override {
        std::cout << "After all cases done, Global" << std::endl;
    }
};

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

    static void SetUpTestCase() {
        std::cout << "SetUpTestCase()" << std::endl;
    }

    static void TearDownTestCase() {
        std::cout << "TearDownTestCase()" << std::endl;
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
    ::testing::AddGlobalTestEnvironment(new GlobalEvent); // add env
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
