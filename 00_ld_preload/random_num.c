//
// Created by jasonkay on 2024/3/10.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL));
  int i = 10;
  while (i--)
    printf("%d\n", rand() % 100);
  return 0;
}
