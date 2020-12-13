#ifndef CPP_LEARN_MUTEX_H
#define CPP_LEARN_MUTEX_H

#include <pthread.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>

class Mutex {
public:
    Mutex();
    ~Mutex();

    void Lock();
    void Unlock();

private:
    pthread_mutex_t mu_{};

    // No copying
    Mutex(const Mutex&);
    void operator=(const Mutex&);
};

#endif //CPP_LEARN_MUTEX_H
