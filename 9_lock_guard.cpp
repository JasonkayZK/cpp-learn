#include <thread>
#include <mutex>
#include <iostream>

int inc_num = 0;
std::mutex inc_mutex;  // ①

void safe_increment() {
    std::lock_guard<std::mutex> lock(inc_mutex);  // ②
    ++inc_num;

    std::cout << std::this_thread::get_id() << ": " << inc_num << '\n'; // ③
}

int main() {
    std::cout << "main: " << inc_num << '\n';

    std::thread t1(safe_increment); // ④
    std::thread t2(safe_increment);

    t1.join();
    t2.join();

    std::cout << "main: " << inc_num << '\n';
    return 0;
}
