//
// Created by JasonkayZK on 2022.06.06.
//

#ifndef COROUTINE_UTILS_H
#define COROUTINE_UTILS_H

#include "coroutine.h"
#include "environment.h"

namespace stack_co {

    namespace this_coroutine {

        inline void yield() {
            return ::stack_co::Coroutine::yield();
        }

    } // this_coroutine

    inline bool test() {
        return Coroutine::test();
    }

    inline Environment &open() {
        return Environment::instance();
    }

} // co

#endif //COROUTINE_UTILS_H
