#include <iostream>

#define LOG(x) (std::cout << "[" << __FILE__ << ":" << __LINE__ << ":" << __PRETTY_FUNCTION__  << "]" << ": " << (x) << std::endl)

void get_type_name() {
  LOG("In the get_type_name!");
}

template<class T>
void func(T a) {
  LOG("In the get_type_name(T)");
}

int main() {
  // 编译期替换为当前文件绝对路径
  std::cout << __FILE__ << std::endl;

  // 编译期替换为代码在当前文件所在行数
  std::cout << __LINE__ << std::endl;

  // 编译期替换为代码所在函数
  std::cout << __func__ << std::endl;

  // 编译期替换为代码所在函数美化版
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  LOG(1);
  get_type_name();
  func(3);
  func(3.3);
}
