#define TRACK_MEMORY
#define PRINT_MEMORY_TRACKING

#include "track_memory.h"

int main() {
  char *buf = new char[100];
  delete[] buf;

  struct TestStruct {
    long a;
    long b;
  };

  auto *testStruct = new TestStruct;
  delete testStruct;
}
