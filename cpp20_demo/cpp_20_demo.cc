#include <coroutine>
#include <iostream>

struct HelloCoroutine {

    struct HelloPromise {

        HelloCoroutine get_return_object() {
            return std::coroutine_handle<HelloPromise>::from_promise(*this);
        }

        std::suspend_never initial_suspend() { return {}; }

        std::suspend_always final_suspend()

        noexcept { return {}; }

        void unhandled_exception() {}
    };

    using promise_type = HelloPromise;

    HelloCoroutine(std::coroutine_handle <HelloPromise> h) : handle(h) {}

    std::coroutine_handle <HelloPromise> handle;
};

HelloCoroutine hello() {
    std::cout << "Hello " << std::endl;
    co_await std::suspend_always{};
    std::cout << "world!" << std::endl;
}

int main() {
    HelloCoroutine coro = hello();

    std::cout << "calling resume" << std::endl;
    coro.handle.resume();

    std::cout << "destroy" << std::endl;
    coro.handle.destroy();

    return 0;
}
