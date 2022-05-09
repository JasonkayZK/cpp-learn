//
// Created by jasonkayzk on 2022/5/8.
//

#include <iostream>
#include <utility>
#include <vector>
#include <string>

class Object {
public:
    explicit Object(std::string str) : _str(std::move(str)) {
        std::cout << "build this object, address: " << this << std::endl;
    }

    virtual ~Object() {
        std::cout << "destruct this object, address: " << this << std::endl;
    }

    Object(const Object &object) = default;

    Object &operator=(const Object &object) = default;

    Object(Object &&object) noexcept {
        std::cout << "move this object!" << std::endl;
    }

    std::string _str;
};

void f_copy(Object obj) {
    std::cout << "copy this object, address: " << &obj << std::endl;
}

void f_move(Object &&obj) {
    std::cout << "move this object, address: " << &obj << std::endl;
}

int main() {
    Object obj{"abc"};

    // function calling
    f_copy(obj);
    f_move(std::move(obj));

    std::cout << obj._str << std::endl; // danger!

    // vector
    std::vector<Object> v;
    v.emplace_back("cba");
}
