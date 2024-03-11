#include <cstdio>
#include <stdlib.h>
#include <string.h>

extern "C" {
void foo() {
  printf("Hi\n");
}

char *hello(const char *str) {
  char *result = (char *) malloc(strlen(str) + 8); // 8 是 "Hi, " 的长度
  if (result == NULL) {
    return NULL; // 内存分配失败
  }

  strcpy(result, "Hi, ");
  strcat(result, str);

  return result;
}

int bar = 200;
}