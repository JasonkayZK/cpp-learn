#ifndef CPP_LEARN_MY_DLL_H
#define CPP_LEARN_MY_DLL_H

#define EXPORT_DLL __declspec(dllexport)

extern "C" EXPORT_DLL int add(int a, int b); // 即 int add(int a,int b)

#endif //CPP_LEARN_MY_DLL_H
