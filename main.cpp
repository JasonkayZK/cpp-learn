#include <iostream>
#include <functional>
#include <vector>

// define functional type
using foo = void(int);

// foo -> foo*
void wrapper_func(foo f) {
    // invoke function
    f(1);
}

void two_invoke_method() {
    auto f = [](int value) {
        std::cout << value << std::endl;
    };
    // f -> foo* type
    wrapper_func(f);
    // lambda invoke
    f(1);
}

int foo2(int para) {
    return para;
}

void wrapper_method() {
    std::function<int(int)> func = foo2;

    int important = 10;
    std::function<int(int)> func2 = [&](int value) -> int {
        return 1 + value + important;
    };

    std::cout << func(10) << std::endl;
    std::cout << func2(10) << std::endl;
}

int foo3(int a, int b, int c) {
    return a + b + c;
}

void placeholder_method() {
    auto bindFoo = std::bind(foo3, std::placeholders::_1, 1, 2);
    std::cout << bindFoo(1) << std::endl;
}

int main() {
//    two_invoke_method();
//    wrapper_method();
    placeholder_method();
}
