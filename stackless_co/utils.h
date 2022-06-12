//
// Created by Jasonkay on 2022/6/12.
//

#ifndef COROUTINE_UTILS_H
#define COROUTINE_UTILS_H

namespace stackless_co {

    class Schedule;

    typedef void (*coroutine_func)(Schedule *, void *ud);
}

#endif //COROUTINE_UTILS_H
