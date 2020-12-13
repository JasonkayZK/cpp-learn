#include "test_mutex_lock.h"
#include <iostream>

#define NUM_THREADS 10000

int num = 0;
Mutex mutex;

void *count([[maybe_unused]] void *args) {
    MutexLock lock(&mutex);
    num++;
}

int main() {
    int t;
    pthread_t thread[NUM_THREADS];

    for (t = 0; t < NUM_THREADS; t++) {
        int ret = pthread_create(&thread[t], nullptr, count, nullptr);
        if (ret) {
            return -1;
        }
    }

    for (t = 0; t < NUM_THREADS; t++)
        pthread_join(thread[t], nullptr);
    std::cout << num << std::endl;
    return 0;
}
