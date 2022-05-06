//
// Created by kylinkzhang on 2022.05.06.
//

#ifndef MYTINYSTL_M_JTHREAD_H
#define MYTINYSTL_M_JTHREAD_H

#include <thread>

namespace mytinystl_utils {

    class m_jthread {
    public:
        template<typename... Args>
        m_jthread(Args &&... args) : _m_thread(std::forward<Args>(args)...) {}

        // move constructor
        m_jthread(m_jthread &&other) noexcept: _m_thread(std::move(other._m_thread)) {}

        // denied copy constructor
        m_jthread(const m_jthread &) = delete;

        // destructor
        ~m_jthread() { if (_m_thread.joinable()) _m_thread.join(); }

        m_jthread &operator=(m_jthread &&other) noexcept {
            m_jthread(std::move(other)).swap(*this);
            return *this;
        }

        void swap(m_jthread &rhs) {
            std::swap(_m_thread, rhs._m_thread);
        }

    private:
        std::thread _m_thread;
    };

}

#endif //MYTINYSTL_M_JTHREAD_H
