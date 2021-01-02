#include <iostream>
#include <chrono>
#include <cmath>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

static const int MAX = 10e7;
static double sum = 0;

// lock
static mutex exclusive;

void concurrent_worker(int min, int max) {
    double tmp_sum = 0;
    for (int i = min; i <= max; i++) {
        tmp_sum += sqrt(i);
    }
    exclusive.lock();
    sum += tmp_sum;
    exclusive.unlock();
}

void concurrent_task(int min, int max) {
    auto start_time = chrono::steady_clock::now();

    // 硬件支持的并发线程数(推荐值)
    unsigned concurrent_count = thread::hardware_concurrency();
    cout << "hardware_concurrency: " << concurrent_count << endl;
    vector<thread> threads;

    // 重置sum
    sum = 0;
    for (int t = 0; t < concurrent_count; t++) {
        int range = max / (int)concurrent_count * (t + 1);
        threads.emplace_back(concurrent_worker, min, range);
        min = range + 1;
    }

    for (auto& t : threads) {
        t.join();
    }

    auto end_time = chrono::steady_clock::now();
    auto ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
    cout << "Concurrent task finish, " << ms << " ms consumed, Result: " << sum << endl;
}

int main() {
    concurrent_task(0, MAX);
    return 0;
}
