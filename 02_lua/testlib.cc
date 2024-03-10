// testlib.cpp

#include <iostream>
#include "lua.hpp"

extern "C" int luaopen_libtestlib(lua_State *L);

using namespace std;

/* 定义C++的Average 函数 */
int average(lua_State *L) {
  int num = lua_gettop(L);  //获取参数个数

  double sum = 0;
  double avg = 0;

  for (int i = 1; i <= num; i++)   //注意Lua栈下标从1开始
  {
    sum += lua_tonumber(L, i);  //求和
  }

  avg = sum / num;   //求平均

  lua_pushnumber(L, avg);  //平均值入栈

  lua_pushnumber(L, sum);  //和入栈

  return 2;   //return 返回值个数
}

/* 定义C++的sub函数 */
int sub(lua_State *L) {
  int num = lua_gettop(L);
  if (num != 2) {
    cout << "Input param number is not correct!" << endl;
    return 0;
  }

  int a = lua_tonumber(L, 1);   //获取第一个参数，被减数
  int b = lua_tonumber(L, 2);   //获取第二个参数，减数

  int diff = a - b;
  lua_pushnumber(L, diff);   //结果压入栈

  return 1;
}

/* 定义C++的add函数 */
int add(lua_State *L) {
  int num = lua_gettop(L);
  if (num != 2) {
    cout << "Input param number is not correct!" << endl;
    return 0;
  }

  int a = lua_tonumber(L, 1);   //获取第一个参数，被减数
  int b = lua_tonumber(L, 2);   //获取第二个参数，减数

  int sum = a + b;
  lua_pushnumber(L, sum);   //结果压入栈

  return 1;
}

//使用luaL_Reg注册新的C函数到Lua中
static luaL_Reg test_functions[] =
    {
        {"average", average},
        {"add", add},
        {"sub", sub},
        {NULL, NULL}   // 数组中最后一对必须是{NULL, NULL}，用来表示结束
    };

/* luaopen_XXX，XXX为库名称，若库名称为testlib.so，XXX即为testlib */
int luaopen_libtestlib(lua_State *L) {
  luaL_newlib(L, test_functions);  //Lua 5.2之后用luaL_newlib代替了luaL_register
  return 1;
}
