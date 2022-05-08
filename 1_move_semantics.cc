//
// Created by jasonkayzk on 2022/5/8.
//

#include <iostream>
#include <utility>

class Object {
public:
    Object() {
        std::cout << "build this object!" << std::endl;
    }

    virtual ~Object() {
        std::cout << "destruct this object, address: " << this << std::endl;
    }

    Object(const Object &object) = default;
};

void f(Object &&obj) {
}

int main() {
    Object obj{};

    // func
    f(std::move(obj));
}
