//
// Created by jasonkay on 2021/5/9.
//

#include <string>
#include <iostream>

bool throw_exception(std::string *ps) {
    return ps->size() > 3;
}

// 1: no memory delete
void memory_leak_1(std::string &str) {
    auto *ps = new std::string(str);

    std::cout << ps->c_str() << std::endl;

    str = *ps;

    // memory leakage if no deletion!
//    delete ps;
}

// 2: returned before memory deletion!
void memory_leak_2(std::string &str) {
    auto *ps = new std::string(str);

    std::cout << ps->c_str() << std::endl;

    // cause memory leakage if thrown exception!
    if (throw_exception(ps)) {
        throw std::exception();
    }

    str = *ps;
    delete ps;
}

int main() {
    std::string str = "cba0";

    for (int i = 0; i < 100000; ++i) {
        try {
            memory_leak_1(str);
            memory_leak_2(str);
        } catch (std::exception e) {
            continue;
        }
    }

    getchar();
    return 0;
}
