#include <iostream>

int main() {

    int foo = 10, bar = 15;
    __asm__ __volatile__("add %%ebx,%%eax"
            :"=a"(foo)
            :"a"(foo), "b"(bar)
            );
    printf("foo+bar=%d\n", foo);

    return 0;
}
