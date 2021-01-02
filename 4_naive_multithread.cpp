#include <iostream>
#include <chrono>
#include <cmath>
#include <thread>
#include <vector>

using namespace std;

static const int MAX = 10e7;
static double sum = 0;

void worker(int min, int max) {
    for (int i = min; i <= max; ++i) {
        sum += std::sqrt(i);
    }
}

void serial_task(int min, int max) {
    auto start_time = chrono::steady_clock::now();
    sum = 0;
    worker(min, max);
    auto end_time = chrono::steady_clock::now();
    auto ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
    cout << "Serial task finish, " << ms << " ms consumed, Result: " << sum << endl;
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
        threads.emplace_back(worker, min, range);
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
    serial_task(0, MAX);
    concurrent_task(0, MAX);
    return 0;
}
