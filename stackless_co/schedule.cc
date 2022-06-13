//
// Created by JasonkayZK on 2022.06.06.
//

#include "utils.h"
#include "schedule.h"
#include "coroutine.h"

#include <cstdlib>
#include <cassert>
#include <cstring>
#include <cstdint>

#if __APPLE__ && __MACH__

#include <sys/ucontext.h>

#else

#include <ucontext.h>

#endif


namespace stackless_co {

    Schedule *Schedule::coroutine_open() {
        auto *s = new(Schedule);
        s->nco = 0;
        s->cap = DEFAULT_COROUTINE;
        s->running = -1;
        s->co = (Coroutine **) malloc(sizeof(Coroutine) * s->cap);
        memset(s->co, 0, sizeof(struct coroutine *) * s->cap);
        return s;
    }

    void Schedule::main_func(uint32_t low32, uint32_t hi32) {
        uintptr_t ptr = (uintptr_t) low32 | ((uintptr_t) hi32 << 32);
        auto *s = (Schedule *) ptr;
        int id = s->running;
        Coroutine *c = s->co[id];
        c->get_func()(s, c->get_ud());
        c->delete_co();
        s->co[id] = nullptr;
        --s->nco;
        s->running = -1;
    }

    void Schedule::coroutine_close() {
        int i;
        for (i = 0; i < this->cap; i++) {
            Coroutine *inner_co = this->co[i];
            if (inner_co) {
                inner_co->delete_co();
            }
        }
        free(this->co);
        this->co = nullptr;
        free(this);
    }

    int Schedule::coroutine_new(coroutine_func func, void *ud) {
        Coroutine *inner_co = Coroutine::new_co(this, func, ud);

        if (this->nco >= this->cap) {
            int id = this->cap;
            this->co = (Coroutine **) realloc(this->co, this->cap * 2 * sizeof(Coroutine));
            memset(this->co + this->cap, 0, sizeof(struct coroutine *) * this->cap);
            this->co[this->cap] = inner_co;
            this->cap *= 2;
            ++this->nco;
            return id;
        } else {
            int i;
            for (i = 0; i < this->cap; i++) {
                int id = (i + this->nco) % this->cap;
                if (this->co[id] == nullptr) {
                    this->co[id] = inner_co;
                    ++this->nco;
                    return id;
                }
            }
        }

        return 0;
    }

    void Schedule::coroutine_resume(int id) {
        assert(this->running == -1);
        assert(id >= 0 && id < this->cap);
        Coroutine *c = this->co[id];
        if (c == nullptr) return;

        int status = c->get_status();
        auto ptr = (uintptr_t) this;
        switch (status) {
            case COROUTINE_READY:

                getcontext(c->get_ctx());
                c->get_ctx()->uc_stack.ss_sp = this->stack;
                c->get_ctx()->uc_stack.ss_size = STACK_SIZE;
                c->get_ctx()->uc_link = &this->main;
                this->running = id;
                c->set_status(COROUTINE_RUNNING);

                makecontext(c->get_ctx(), (void (*)()) main_func, 2, (uint32_t) ptr, (uint32_t) (ptr >> 32));
                swapcontext(&this->main, c->get_ctx());
                break;
            case COROUTINE_SUSPEND:
                memcpy(this->stack + STACK_SIZE - c->get_size(), c->get_stack(), c->get_size());
                this->running = id;
                c->set_status(COROUTINE_RUNNING);
                swapcontext(&this->main, c->get_ctx());
                break;
            default:
                assert(0);
        }
    }

    int Schedule::coroutine_status(int id) {
        assert(id >= 0 && id < this->cap);
        if (this->co[id] == nullptr) {
            return COROUTINE_DEAD;
        }
        return this->co[id]->get_status();
    }

    int Schedule::coroutine_running() const {
        return this->running;
    }

    void Schedule::coroutine_yield() {
        int id = this->running;
        assert(id >= 0);
        Coroutine *c = this->co[id];
        assert((char *) &c > this->stack);
        _save_stack(c, this->stack + STACK_SIZE);
        c->set_status(COROUTINE_SUSPEND);
        this->running = -1;
        swapcontext(c->get_ctx(), &this->main);
    }

    void Schedule::_save_stack(Coroutine *c, char *top) {
        char dummy = 0;
        assert(top - &dummy <= STACK_SIZE);
        if (c->get_cap() < top - &dummy) {
            free(c->get_stack());
            c->set_cap(top - &dummy);
            c->set_stack(static_cast<char *>(malloc(c->get_cap())));
        }

        c->set_size(top - &dummy);
        memcpy(c->get_stack(), &dummy, c->get_size());
    }

} // namespace stackless_co