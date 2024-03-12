//
// Created by jasonkay on 2024/3/12.
//

#include <gtest/gtest.h>
#include <hello.h>

#include <cstdlib>
#include <fstream>

const char *g_Test_v1 = R"delimiter(
extern "C" {
int foo(int x) {
    return x + 5;
}
int bar = 3;
}
)delimiter";

const char *g_Test_v2 = R"delimiter(
extern "C" {
int foo(int x) {
    return x - 5;
}
int bar = -2;
}
)delimiter";

class ReloadTest : public ::testing::Test {
 public:
  // Called automatically at the start of each test case.
  void SetUp() override {
    WriteFile("hello/src/hello.cc", g_Test_v1);
    Compile(1);
    HelloModule::LoadLibrary();
  }

  // We'll invoke this function manually in the middle of each test case
  void ChangeAndReload() {
    WriteFile("hello/src/hello.cc", g_Test_v2);
    Compile(2);
    HelloModule::ReloadLibrary();
  }

  // Called automatically at the end of each test case.
  void TearDown() override {
    HelloModule::UnloadLibrary();
    WriteFile("hello/src/hello.cc", g_Test_v1);
    Compile(1);
  }

 private:
  static void WriteFile(const char *path, const char *text) {
    // Open an output filestream, deleting existing contents
    std::ofstream out(path, std::ios_base::trunc | std::ios_base::out);
    out << text;
  }

  void Compile(int version) {
    if (version == m_version) {
      return;
    }

    m_version = version;
    EXPECT_EQ(std::system("cmake --build build"), 0);

    // Super unfortunate sleep due to the result of cmake not being fully
    // flushed by the time the command returns (there are more elegant ways
    // to solve this)
    sleep(1);
  }

  int m_version = 1;
};

TEST_F(ReloadTest, VariableReload
) {
  EXPECT_EQ(HelloModule::GetBar(),
            3);
  ChangeAndReload();
  EXPECT_EQ(HelloModule::GetBar(),
            -2);
}

TEST_F(ReloadTest, FunctionReload
) {
  EXPECT_EQ(HelloModule::Foo(4),
            9);
  ChangeAndReload();
  EXPECT_EQ(HelloModule::Foo(4),
            -1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
