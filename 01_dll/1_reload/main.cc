//
// Created by jasonkay on 2024/3/11.
//

#include <cstdio>
#include <string>

#include "reload.h"

const char *g_libPath = "libhello.so";

int main() {
  const char *name = "Jack";

  void *handle;
  void (*foo)();
  char *(*hello)(const char *);
  int bar;

  handle = reload::load(g_libPath);
  if (!handle) {
    reload::printError();
    return -1;
  }
  foo = reinterpret_cast<void (*)()>(reload::loadSymbol(handle, "foo"));
  foo();
  bar = *reinterpret_cast<int *>(reload::loadSymbol(handle, "bar"));
  printf("bar == %d\n", bar);
  hello = reinterpret_cast<char *(*)(const char *)>(reload::loadSymbol(handle, "hello"));
  printf("Hello func: %s\n", hello(name));

  printf("\n[INFO] Now modify the source code and recompile the library...\n");
  printf("[INFO] Press any key to continue...\n");
  getchar();

  ///  Modify the source code and recompile the library.
  std::string filename = "hello.cc";
  // MacOS sed
//  std::string command = std::string("sed -i '' ") +
  std::string command = std::string("sed -i ") +
      (bar == 200 ? "'s/200/300/'" : "'s/300/200/'") + " " +
      filename;
  system(command.c_str());
  // MacOS sed
//  command = std::string("sed -i '' ") +
  command = std::string("sed -i ") +
      (bar == 200 ? "'s/Hi/Hello/'" : "'s/Hello/Hi/'") + " " + filename;
  system(command.c_str());
  system("g++ -shared -fPIC -o libhello.so hello.cc");

  reload::reload(handle, g_libPath);
  if (!handle) {
    reload::printError();
    return -1;
  }

  foo = reinterpret_cast<void (*)()>(reload::loadSymbol(handle, "foo"));
  foo();
  bar = *reinterpret_cast<int *>(reload::loadSymbol(handle, "bar"));
  printf("bar == %d\n", bar);
  hello = reinterpret_cast<char *(*)(const char *)>(reload::loadSymbol(handle, "hello"));
  printf("Hello func: %s\n", hello(name));

  return 0;
}
