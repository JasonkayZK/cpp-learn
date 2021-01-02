#include <iostream>
#include <thread>

void hello_with_id(const int threadId) {
    std::cout << "Hello World from thread-" << threadId << std::endl;
}

void hello() {
    std::cout << "Hello World from new thread." << std::endl;
}

int main() {
    std::cout << "main start" << std::endl;

    std::thread t(hello);
    std::thread t1([] { hello_with_id(1); });
    std::thread t2([] { hello_with_id(2); });
    std::thread t3(hello_with_id, 3);

    t.join();
    t1.join();
    t2.join();
    t3.join();

    std::cout << "main end" << std::endl;
    return 0;
}
