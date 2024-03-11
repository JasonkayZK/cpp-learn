//
// Created by jasonkay on 2024/3/11.
//

#ifndef CPP_LEARN_01_DLL_1_RELOAD_RELOAD_H_
#define CPP_LEARN_01_DLL_1_RELOAD_RELOAD_H_

#include <dlfcn.h>
#include <cstdio>

namespace reload {

inline void *load(const char *filepath) {
  return dlopen(filepath, RTLD_LAZY);
}

inline void *loadSymbol(void *library, const char *symbol) {
  return dlsym(library, symbol);
}

inline void reload(void *&library, const char *filepath) {
  if (library) {
    dlclose(library);
  }
  library = load(filepath);
}

inline void printError() {
  fprintf(stderr, "%s\n", dlerror());
}

}

#endif //CPP_LEARN_01_DLL_1_RELOAD_RELOAD_H_
