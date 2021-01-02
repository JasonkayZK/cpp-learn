#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>

using namespace std;

void print_time() {
    // 获取当前系统当前时间time_point
    auto now = chrono::system_clock::now();
    // 将time_point转换成time_t秒
    auto in_time_t = chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << put_time(localtime(&in_time_t), "%Y-%m-%d %X");
    cout << "now is: " << ss.str() << endl;
}

void sleep_thread() {
    this_thread::sleep_for(chrono::seconds(3));
    cout << "[thread-" << this_thread::get_id() << "] is waking up" << endl;
}

void loop_thread() {
    for (int i = 0; i < 10; i++) {
        cout << "[thread-" << this_thread::get_id() << "] print: " << i << endl;
    }
}

int main() {
    print_time();

    thread t1(sleep_thread);
    thread t2(loop_thread);

    t1.join();
    t2.detach();

    print_time();
    return 0;
}
