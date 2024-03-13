//
// Created by jasonkay on 2024/3/13.
//
#include <iostream>

template<class T>
std::string get_type_name() {
  std::string s = __PRETTY_FUNCTION__;
  auto pos = s.find("T = ");
  pos += 4;
  auto pos2 = s.find_first_of(";]", pos);
  return s.substr(pos, pos2 - pos);
}

template<class T, T N>
std::string get_int_name() {
  std::string s = __PRETTY_FUNCTION__;
  auto pos = s.find("N = ");
  pos += 4;
  auto pos2 = s.find_first_of(";]", pos);
  return s.substr(pos, pos2 - pos);
}

template<int N>
struct int_constant {
  static constexpr int value = N;
};

template<int Beg, int End, class F>
void static_for(F const &f) {
  if constexpr (Beg == End) {
    return;
  } else {
    f(int_constant<Beg>());
    static_for<Beg + 1, End>(f);
  }
}

template<class T>
std::string get_int_name_dynamic(T n) {
  std::string ret;
  static_for<0, 3>([&](auto ic) {
    if (n == (T) ic.value) {
      ret = get_int_name<T, (T) ic.value>();
    }
  });
  return ret;
}

namespace MyUtils {
struct MyClass;
}

enum Color {
  RED = 1, GREEN = 2, BLUE = 3,
};

int main() {
  // 类型反射
  std::cout << get_type_name<MyUtils::MyClass>() << std::endl;
  std::cout << get_type_name<std::string>() << std::endl;

  std::cout << get_int_name<char, 1>() << std::endl;
  std::cout << get_int_name<Color, Color(1)>() << std::endl;
  std::cout << get_int_name<Color, Color(4)>() << std::endl;

  constexpr auto c = RED;
  std::cout << get_int_name<Color, c>() << std::endl;

  auto d = GREEN;
  std::cout << get_int_name_dynamic(d) << std::endl;

  return 0;
}
