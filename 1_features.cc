//
// Created by jasonkay on 2024/3/5.
//
#include <dbg.h>

void multiple_args() {
  dbg("\nmultiple_args");

  dbg(42, "hello world", false);

  // wrap "unprotected commas" in parentheses
  dbg("a vector:", (std::vector<int>{2, 3, 4}));
}

void binary_format() {
  dbg("\nbinary_format");

  const uint32_t secret = 12648430;
  dbg(dbg::hex(secret));
}

template<typename T>
void type_names() {
  dbg("\ntype_names");

  using MyDependentType = typename std::remove_reference<T>::type &&;
  dbg(dbg::type<MyDependentType>());
}

void current_time() {
  dbg("\ncurrent_time");

  dbg(dbg::time());
}

int main() {
  multiple_args();

  binary_format();

  type_names<long long>();

  current_time();

  return 0;
}
