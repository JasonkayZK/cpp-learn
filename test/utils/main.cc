//
// Created by kylinkzhang on 2022.05.07.
//

#include <condition_variable>
#include <iostream>
#include <mutex>

#include "m_function.h"
#include "m_jthread.h"
#include "m_log.h"
#include "m_test_util.h"

#include "gtest/gtest.h"

TEST(TestUtilTest, CalculateTime) {
  auto f1 = [](int i, int j, int k) -> std::vector<int> {
    std::vector<int> r(i * j * k);
    size_t cnt = 0;
    for (int x = 1; x <= i; ++x) {
      for (int y = 1; y <= j; ++y) {
        for (int z = 1; z <= k; ++z) {
          r[cnt++] = x * y * z;
        }
      }
    }
    return r;
  };

  auto f2 = [](int i, int j, int k) -> void {
    for (int x = 1; x <= i; ++x) {
      for (int y = 1; y <= j; ++y) {
        for (int z = 1; z <= k; ++z) {
        }
      }
    }
  };

  auto r1 = mytinystl_utils::calculate_time_with_return(f1, 100, 100, 100);
  std::cout << "time: " << r1._time_ms << "ms\n";
  EXPECT_EQ(r1._data[r1._data.size() - 1], 1000000);

  auto r2 = mytinystl_utils::calculate_time(f2, 100, 100, 100);
  std::cout << "time: " << r2._time_ms << "ms\n";
}

TEST(LogTest, Base) {
  auto f = [](int x, int y) -> int {
    if (y == 0) {
      throw std::runtime_error("Zero can't be divisor.");
    }
    return x / y;
  };
  try {
    f(1, 0);
  } catch (std::runtime_error &e) {
    EXPECT_EQ(mytinystl_utils::m_log(e.what()), 0);
  }

  EXPECT_EQ(mytinystl_utils::m_log("haha\n", "game over"), 0);
}

TEST(FunctionTest, HasFunc) {
  struct Obj {
    void reserve(size_t i){};

    void emplace_back(Obj obj){};
  };

  using type_v = std::vector<Obj>;

  EXPECT_EQ(mytinystl_utils::m_has_reserve<type_v>::value, true);
  EXPECT_EQ(mytinystl_utils::m_has_reserve<Obj>::value, true);
  EXPECT_EQ(mytinystl_utils::m_has_resize<type_v>::value, true);
  EXPECT_EQ(mytinystl_utils::m_has_resize<Obj>::value, false);
}

TEST(CompositeTest, CompositeFunc) {

  auto f1 = [](auto &&v) { return v + v; };

  auto f2 = [](auto &&v) { return v * v; };

  EXPECT_EQ(mytinystl_utils::m_composite_fun(f1, f2)(10), 200);
}

TEST(JThreadTest, JThread) {
  std::mutex mtx01;
  std::condition_variable cv;
  bool ready = false;

  auto fun = [&mtx01, &cv, &ready](int i) {
    std::unique_lock<std::mutex> lck(mtx01);
    while (!ready) {
      cv.wait(lck);
    }
    mytinystl_utils::m_log("thread", i);
  };

  auto start = [&mtx01, &cv, &ready]() {
    std::unique_lock<std::mutex> lck(mtx01);
    ready = true;
    cv.notify_one();
  };

  const int N = 10;
  mytinystl_utils::m_jthread threads[N];
  for (int i = 0; i < N; ++i) {
    threads[i] = mytinystl_utils::m_jthread(fun, i);
  }
  start();
}

int main(int argc, char *argv[]) {
  printf("Running main() from %s\n", __FILE__);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
