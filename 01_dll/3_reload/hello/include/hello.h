//
// Created by jasonkay on 2024/3/12.
//

#ifndef CPP_LEARN_01_DLL_3_RELOAD_HELLO_HELLO_H_
#define CPP_LEARN_01_DLL_3_RELOAD_HELLO_HELLO_H_

#include <array>

#include "reload.h"

inline std::array<const char *, 3> g_exports = {"foo", "bar", "hello"};

class HelloModule : public ReloadModule<HelloModule, g_exports.size()> {
 public:
  static void Foo() { GetInstance().Execute<void>("foo"); }

  static int GetBar() { return *GetInstance().GetVar<int>("bar"); }

  static char *Hello(const char *str) {
    return GetInstance().Execute<char *, const char *>("hello", str);
  }

 protected:
  [[nodiscard]] const char *GetPath() const override {
    // MacOS generate dylib
//    return "./build/hello/libhello.dylib";

    return "./build/hello/libhello.so";
  }

  [[nodiscard]] std::array<const char *, g_exports.size()> &GetSymbolNames()
  const override {
    return g_exports;
  }
};

#endif //CPP_LEARN_01_DLL_3_RELOAD_HELLO_HELLO_H_
