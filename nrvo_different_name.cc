#include <cstdio>

class RVO {
public:

    RVO() { printf("I am in constructor\n"); }

    RVO(const RVO &c_RVO) { printf("I am in copy constructor\n"); }

    int mem_var{};
};

RVO MyMethod(int i) {
    RVO rvo;
    rvo.mem_var = i;
    if (rvo.mem_var == 10)
//        return (RVO());
        return rvo;
    return rvo;
}

int main() {
    RVO rvo;
    rvo = MyMethod(5);
}
