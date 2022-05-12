//
// Created by Jasonkay on 2022/5/12.
//
#include <cstdio>

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
    throw "I am throwing an exception!";
    return (rvo);
}

int main() {
    RVO rvo;
    try {
        rvo = MyMethod(5);
    }
    catch (const char *str) {
        printf("I caught the exception\n");
    }

    return 0;
}
