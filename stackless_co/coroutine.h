//
// Created by Jasonkay on 2022/6/6.
//

#ifndef COROUTINE_COROUTINE_H
#define COROUTINE_COROUTINE_H

#include "utils.h"
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

    class Schedule;

    class Coroutine {
    public:

        static Coroutine *new_co(Schedule *s, coroutine_func func, void *ud);

        void delete_co();

        inline coroutine_func get_func() {
            return func;
        }

        inline ucontext_t *get_ctx() {
            return &ctx;
        }

        inline int get_status() {
            return status;
        }

        inline ptrdiff_t get_size() {
            return this->size;
        }

        inline char *get_stack() {
            return this->stack;
        }

        inline ptrdiff_t get_cap() {
            return this->cap;
        }

        inline void set_status(int status) {
            this->status = status;
        }

        inline void set_stack(char *stack) {
            this->stack = stack;
        }

        inline void set_cap(ptrdiff_t cap) {
            this->cap = cap;
        }

        inline void set_size(ptrdiff_t size) {
            this->size = size;
        }

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
