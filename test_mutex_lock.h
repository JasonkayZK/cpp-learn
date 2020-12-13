#ifndef CPP_LEARN_TEST_MUTEX_LOCK_H
#define CPP_LEARN_TEST_MUTEX_LOCK_H

#include "mutex.h"

class  MutexLock {
public:
    explicit MutexLock(Mutex *mu)
            : mu_(mu)  {
        this->mu_->Lock();
    }
    ~MutexLock() { this->mu_->Unlock(); }

private:
    Mutex *const mu_;

    // No copying allowed
    MutexLock(const MutexLock&);
    void operator=(const MutexLock&);
};

#endif //CPP_LEARN_TEST_MUTEX_LOCK_H
