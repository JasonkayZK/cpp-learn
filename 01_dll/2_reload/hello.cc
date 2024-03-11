#include <cstdio>
#include <stdlib.h>
#include <string.h>

extern "C" {
void foo() {
  printf("Hello\n");
}

char *hello(const char *str) {
  char *result = (char *) malloc(strlen(str) + 8); // 8 是 "Hello, " 的长度
  if (result == NULL) {
    return NULL; // 内存分配失败
  }

  strcpy(result, "Hello, ");
  strcat(result, str);

  return result;
}

int bar = 300;
}