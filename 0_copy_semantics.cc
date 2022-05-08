//
// Created by jasonkayzk on 2022/5/8.
//

#include <iostream>
#include <vector>
#include <string>

class Object {
public:
    Object() {
        std::cout << "build this object!" << std::endl;
    }

    virtual ~Object() {
        std::cout << "destruct this object!" << std::endl;
    }
};

void f(const Object obj) {}

int main() {
    Object obj{};

    // function calling
    f(obj);

    // vector
    std::vector<Object> v;
    v.push_back(obj);
}
