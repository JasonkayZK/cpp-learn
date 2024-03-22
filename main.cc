#include <iostream>
//
// Created by jasonkay on 2024/3/22.
//
extern "C" {
void *malloc(size_t size);

void free(void *block);

void print_mem_list();
}

int main() {
  int *p_int = static_cast<int *>(malloc(sizeof(int *)));
  *p_int = 1;
  std::cout << "Int pointer Address: " << p_int << ", val: " << *p_int << std::endl;
  print_mem_list();

  double *p_double = static_cast<double *>(malloc(sizeof(double *)));
  *p_double = 1.5;
  std::cout << "Double pointer Address: " << p_double << ", val: " << *p_double << std::endl;
  print_mem_list();

  int char_size = 16;
  char *p_string = static_cast<char *>(malloc(char_size * sizeof(char)));
  for (int i = 0; i < char_size; ++i) {
    p_string[i] = 'A' + i;
  }
  std::cout << "String pointer Address: " << p_string << ", val: " << *p_string << std::endl;
  print_mem_list();

  free(p_int);
  std::cout << "After free int pointer, address: " << p_int << std::endl;
  print_mem_list();

  free(p_string);
  std::cout << "After free string pointer, address: " << p_string << std::endl;
  print_mem_list();

  free(p_double);
  std::cout << "After free double pointer, address: " << p_double << std::endl;
  print_mem_list();

  return 0;
}
