//
// Created by jasonkay on 2024/3/12.
//

#include <hello.h>

#include <iostream>

int main() {
  const char *name = "Jack";

  HelloModule::LoadLibrary();
  HelloModule::Foo();
  int bar = HelloModule::GetBar();
  std::cout << "bar == " << bar << std::endl;
  std::cout << "Hello func: " << HelloModule::Hello(name) << std::endl;


  // Modify the source code and recompile the library.
  std::string filename = "./hello/src/hello.cc";
  // MacOS sed
  std::string command = std::string("sed -i '' ") +
//  std::string command = std::string("sed -i ") +
      (bar == 200 ? "'s/200/300/'" : "'s/300/200/'") + " " +
      filename;
  system(command.c_str());
  // MacOS sed
  command = std::string("sed -i '' ") +
//  command = std::string("sed -i ") +
      (bar == 200 ? "'s/Hi/Hello/'" : "'s/Hello/Hi/'") + " " + filename;
  system(command.c_str());
  system("cmake --build build");

  HelloModule::ReloadLibrary();
  HelloModule::Foo();
  std::cout << "bar == " << HelloModule::GetBar() << std::endl;
  std::cout << "Hello func: " << HelloModule::Hello(name) << std::endl;

  return 0;
}
