#include <iostream>
#include "gtest/gtest.h"

TEST(HelloTest, PrintHello) {
    std::string str{"Hello, World!"};
    ASSERT_EQ(str, "Hello, World!");
    ASSERT_EQ(str.size(), 13);
}

int main(int argc, char **argv) {
    printf("Running main() from %s\n", __FILE__);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
