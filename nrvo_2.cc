//
// Created by JasonkayZK on 2022.05.11.
//

#include <iostream>

class A {
public:
    A() {
        printf("A: I am in constructor\n");
        i = 1;
    }

    ~A() {
        printf("A: I am in destructor\n");
        i = 0;
    }

    A(const A &a) {
        printf("A: I am in copy constructor\n");
        i = a.i;
    }

    int i, x{}, w{};
};

class B {
public:
    A a;

    B() { printf("B: I am in constructor\n"); }

    ~B() { printf("B: I am in destructor\n"); }

    B(const B &b) { printf("B: I am in copy constructor\n"); }
};

A MyMethod() {
    B *b = new B();
    A a = b->a;
    delete b;
    return (a);
}

int main() {
    A a;
    a = MyMethod();
}
