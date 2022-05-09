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

    Object(const Object &object) : _str(object._str) {
        std::cout << "copy this object, address: " << this << std::endl;
    }

    Object(Object &&object) noexcept: _str(std::move(object._str)) {
        std::cout << "move this object!" << std::endl;
    }

    std::string _str;
};

template<typename T>
void f_forward(T &&t) {

    Object a = std::forward<T>(t);

    std::cout << "forward this object, address: " << &a << std::endl;
}

int main() {
    Object obj{"abc"};
    f_forward(obj);

    f_forward(Object("def"));

    return 0;
}
