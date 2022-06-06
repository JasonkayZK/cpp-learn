//
// Created by Jasonkay on 2022/6/6.
//

#ifndef COROUTINE_COROUTINE_H
#define COROUTINE_COROUTINE_H

#include "schedule.h"

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstddef>
#include <cstring>
#include <cstdint>

#if __APPLE__ && __MACH__
#include <sys/ucontext.h>
#else

#include <ucontext.h>

#endif

namespace stackless_co {

    class Coroutine {
    public:

        static Coroutine *new_co(struct schedule *s, coroutine_func func, void *ud);

        void delete_co();

    private:
        coroutine_func func;
        void *ud;
        ucontext_t ctx;
        Schedule *sch;
        ptrdiff_t cap;
        ptrdiff_t size;
        int status;
        char *stack;
    };

} // stackless_co

#endif //COROUTINE_COROUTINE_H
