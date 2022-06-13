//
// Created by Jasonkay on 2022/6/5.
//

#ifndef COROUTINE_COROUTINE_H
#define COROUTINE_COROUTINE_H

#include "status.h"
#include "context.h"

#include <functional>
#include <memory>

namespace stack_co {

    class Environment;

    class Coroutine : public std::enable_shared_from_this<Coroutine> {
        friend class Environment;

        friend class Context;

    public:
        static Coroutine &current();

        // 测试当前控制流是否位于协程上下文
        static bool test();

        // 获取当前运行时信息
        // 目前仅支持运行、退出、主协程的判断
        Status runtime() const;

        bool exit() const;

        bool running() const;

        // 核心操作：resume和yield

        // usage: Coroutine::current().yield()
        static void yield();

        // Note1: 允许处于EXIT状态的协程重入，从而再次resume
        //        如果不使用这种特性，则用exit() / running()判断
        //
        // Note2: 返回值可以得知resume并执行后的运行时状态
        //        但是这个值只适用于简单的场合
        //        如果接下来其它协程的运行也影响了该协程的状态
        //        那建议用runtime()获取
        Status resume();

        Coroutine(const Coroutine &) = delete;

        Coroutine(Coroutine &&) = delete;

        Coroutine &operator=(const Coroutine &) = delete;

        Coroutine &operator=(Coroutine &&) = delete;

        // 由于用到std::make_shared，必须公开这个构造函数
        // TODO 设为private
    public:

        // 构造Coroutine执行函数，entry为函数入口，对应传参为arguments...
        // Note: 出于可重入的考虑，entry强制为值语义
        template<typename Entry, typename ...Args>
        Coroutine(Environment *master, Entry entry, Args ...arguments)
                : _entry([=] { entry(/*std::move*/(arguments)...); }),
                  _master(master) {}

    private:
        static void call_when_finish(Coroutine *coroutine);

    private:
        Status _runtime{};

        Context _context;

        std::function<void()> _entry;

        Environment *_master;
    };

} // namespace stack_co

#endif //COROUTINE_COROUTINE_H
