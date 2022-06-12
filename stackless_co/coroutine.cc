//
// Created by Jasonkay on 2022/6/6.
//

#include "utils.h"
#include "coroutine.h"
#include "schedule.h"

namespace stackless_co {

    Coroutine *Coroutine::new_co(Schedule *s, coroutine_func func, void *ud) {
        auto *co = new(Coroutine);
        co->func = func;
        co->ud = ud;
        co->cap = 0;
        co->size = 0;
        co->status = Schedule::COROUTINE_READY;
        co->stack = nullptr;
        return co;
    }

    void Coroutine::delete_co() {
        free(this->stack);
        free(this);
    }

} // stackless_co