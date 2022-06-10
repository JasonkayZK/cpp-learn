#include <iostream>

int main() {
    std::cout << "/*";
    std::cout << "*/";
    std::cout << /* "/*" */ "abc";
    std::cout << /* "*/" /* " /*" */;

    return 0;
}
