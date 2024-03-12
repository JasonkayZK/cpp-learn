#ifndef CPP_LEARN_01_DLL_3_RELOAD_RELOAD_INCLUDE_RELOAD_H_
#define CPP_LEARN_01_DLL_3_RELOAD_RELOAD_INCLUDE_RELOAD_H_

#include <dlfcn.h>

#include <array>
#include <iostream>
#include <string>
#include <unordered_map>

template<typename E, size_t NumSymbols>
class ReloadModule {
 public:
  static void LoadLibrary() { GetInstance().Load(); }
  static void ReloadLibrary() { GetInstance().Reload(); }

 protected:
  static E &GetInstance() {
    static E instance;
    return instance;
  }

  // Should return the path to the library on disk
  virtual const char *GetPath() const = 0;

  // Should return a reference to an array of C-strings of size NumSymbols
  // Used when loading or reloading the library to lookup the address of
  // all exported symbols
  virtual std::array<const char *, NumSymbols> &GetSymbolNames() const = 0;

  template<typename Ret, typename... Args>
  Ret Execute(const char *name, Args... args) {
    // Lookup the function address
    auto symbol = m_symbols.find(name);
    if (symbol != m_symbols.end()) {
      // Cast the address to the appropriate function type and call it,
      // forwarding all arguments
      return reinterpret_cast<Ret (*)(Args...)>(symbol->second)(args...);
    }
    throw std::runtime_error(std::string("Function not found: ") + name);
  }

  template<typename T>
  T *GetVar(const char *name) {
    auto symbol = m_symbols.find(name);
    if (symbol != m_symbols.end()) {
      return static_cast<T *>(symbol->second);
    }
    // We didn't find the variable. Return an empty pointer
    return nullptr;
  }

 private:
  void Load() {
    m_libHandle = dlopen(GetPath(), RTLD_NOW);
    LoadSymbols();
  }

  void Reload() {
    auto ret = dlclose(m_libHandle);
    m_symbols.clear();
    Load();
  }

  void LoadSymbols() {
    for (const char *symbol : GetSymbolNames()) {
      auto *sym = dlsym(m_libHandle, symbol);
      m_symbols[symbol] = sym;
    }
  }

  void *m_libHandle;
  std::unordered_map<std::string, void *> m_symbols;
};

#endif //CPP_LEARN_01_DLL_3_RELOAD_RELOAD_INCLUDE_RELOAD_H_
