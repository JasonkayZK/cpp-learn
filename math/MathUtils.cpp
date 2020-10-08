//
// Created by Jasonkay on 2020/10/8.
//

#include <cstdio>
#include "MathUtils.h"

int hello(int num) {
    printf("Hello World From MathUtils! Result is %d\n", num * 2);
    return num * 2;
}

double power(double base, int exponent) {
    int result = base;
    int i;

    if (exponent == 0) {
        return 1;
    }

    for (i = 1; i < exponent; ++i) {
        result = result * base;
    }

    return result;
}
