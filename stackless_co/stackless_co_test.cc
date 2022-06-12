//
// Created by JasonkayZK on 2022.06.06.
//

#include "schedule.h"

#include <cstdio>

struct args {
    int n;
};

void foo(stackless_co::Schedule *s, void *ud) {
    args *arg = static_cast<args *>(ud);
    int start = arg->n;
    for (int i = 0; i < 5; i++) {
        printf("coroutine %d : %d\n", s->coroutine_running(), start + i);
        s->coroutine_yield();
    }
}

void test(stackless_co::Schedule *s) {
    struct args arg1 = {0};
    struct args arg2 = {100};

    int co1 = s->coroutine_new(foo, &arg1);
    int co2 = s->coroutine_new(foo, &arg2);
    printf("main start\n");

    while (s->coroutine_status(co1) && s->coroutine_status(co2)) {
        s->coroutine_resume(co1);
        s->coroutine_resume(co2);
    }
    printf("main end\n");
}

int main() {
    auto *s = stackless_co::Schedule::coroutine_open();
    test(s);
    s->coroutine_close();

    return 0;
}
