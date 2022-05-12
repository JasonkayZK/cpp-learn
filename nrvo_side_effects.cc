//
// Created by Jasonkay on 2022/5/12.
//
#include <cstdio>

int NumConsCalls = 0;
int NumCpyConsCalls = 0;

class RVO {
public:
    RVO() { NumConsCalls++; }

    RVO(const RVO &c_RVO) { NumCpyConsCalls++; }
};

RVO MyMethod() {
    RVO rvo;
    return (rvo);
}

int main() {
    RVO rvo;
    rvo = MyMethod();
    int Division = NumConsCalls / NumCpyConsCalls;
    printf("Constructor calls / Copy constructor calls = %d\n", Division);

    return 0;
}
