//
// Created by JasonkayZK on 2022.06.06.
//

#include "schedule.h"

namespace stackless_co {

    Schedule *Schedule::coroutine_open() {
        return nullptr;
    }

    void Schedule::main_func(uint32_t low32, uint32_t hi32) {

    }

    void Schedule::coroutine_close() {

    }

    int Schedule::coroutine_new(coroutine_func, void *ud) {
        return 0;
    }

    void Schedule::coroutine_resume(int id) {

    }

    int Schedule::coroutine_status(int id) {
        return 0;
    }

    int Schedule::coroutine_running() {
        return 0;
    }

    void Schedule::coroutine_yield() {

    }

    void Schedule::_save_stack(struct coroutine *C, char *top) {

    }

} // stackless_co