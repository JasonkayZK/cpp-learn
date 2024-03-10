//
// Created by jasonkay on 2024/3/10.
//
#include <iostream>
#include <lua.hpp>

int main() {
  //1.创建Lua状态
  lua_State *L = luaL_newstate();
  if (L == nullptr) {
    return -1;
  }

  //2.加载Lua文件
  int bRet = luaL_loadfile(L, "hello.lua");
  if (bRet) {
    std::cout << "load file error" << std::endl;
    return -1;
  }

  //3.运行Lua文件
  bRet = lua_pcall(L, 0, 0, 0);
  if (bRet) {
    std::cout << "pcall error" << std::endl;
    return -1;
  }

  //4.读取变量
  lua_getglobal(L, "total");
  int total = lua_tointeger(L, -1);
  std::cout << "total = " << total << std::endl;        //str = I am so cool~

  //7.关闭state
  lua_close(L);

  return 0;
}
