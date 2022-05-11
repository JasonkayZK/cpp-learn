//
// Created by JasonkayZK on 2022.05.11.
//

#include <iostream>

class RVO {
public:

    RVO() { printf("I am in constructor\n"); }

    RVO(const RVO &c_RVO) { printf("I am in copy constructor\n"); }

    ~RVO() { printf("I am in destructor\n"); }

    int mem_var{};
};

RVO MyMethod(int i) {
    RVO rvo;
    rvo.mem_var = i;
    return (rvo);
}

int main() {
    RVO rvo;
    rvo = MyMethod(5);
}
