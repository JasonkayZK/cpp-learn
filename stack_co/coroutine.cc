//
// Created by Jasonkay on 2022/6/5.
//

#include "coroutine.h"
#include "environment.h"

namespace stack_co {

    Coroutine &Coroutine::current() {
        return *Environment::instance().current();
    }

    bool Coroutine::test() {
        return current()._context.test();
    }

    const Status Coroutine::runtime() const {
        return _runtime;
    }

    bool Coroutine::exit() const {
        return _runtime & Status::EXIT;
    }

    bool Coroutine::running() const {
        return _runtime & Status::RUNNING;
    }

    const Status Coroutine::resume() {
        if (!(_runtime & Status::RUNNING)) {
            _context.prepare(Coroutine::call_when_finish, this);
            _runtime |= Status::RUNNING;
            _runtime &= ~Status::EXIT;
        }
        auto previous = _master->current();
        _master->push(shared_from_this());
        _context.switch_from(&previous->_context);
        return _runtime;
    }

// usage: Coroutine::current().yield()
// void Coroutine::yield() {
//     if(&current() != this) {
//         throw std::runtime_error("cannot yield");
//     }
//     _master->pop();
//     current()._context.switchFrom(&_context);
// }

    void Coroutine::yield() {
        auto &coroutine = current();
        auto &currentContext = coroutine._context;

        coroutine._master->pop();

        auto &previousContext = current()._context;
        previousContext.switch_from(&currentContext);
    }

    void Coroutine::call_when_finish(Coroutine *coroutine) {
        auto &routine = coroutine->_entry;
        auto &runtime = coroutine->_runtime;
        if (routine) routine();
        runtime ^= (Status::EXIT | Status::RUNNING);
        // coroutine->yield();
        yield();
    }

} // co

