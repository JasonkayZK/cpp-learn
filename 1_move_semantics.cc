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

void f_copy(Object obj) {
    std::cout << "copy function, address: " << &obj << std::endl;
}

void f_move(Object &&obj) {
    Object a_obj(std::move(obj));
    std::cout << "move function, address: " << &a_obj << std::endl;
}

int main() {
    Object obj{"abc"};

    // function calling
    f_copy(obj);
    f_move(std::move(obj));

//    std::cout << obj._str << std::endl; // danger!

    std::cout << "============== end ================" << std::endl;

    return 0;
}
