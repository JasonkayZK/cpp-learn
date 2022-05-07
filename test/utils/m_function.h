//
// Created by kylinkzhang on 2022.05.07.
//

#ifndef MYTINYSTL_FUNCTION_H
#define MYTINYSTL_FUNCTION_H

#include <type_traits>
#include <vector>

namespace mytinystl_utils {

    // for template cases
    template<typename...>
    using m_void = void;
    // for template cases
    struct m_false {
        constexpr static bool value{false};
    };
    struct m_true {
        constexpr static bool value{true};
    };

    // m_has_resize
    template<typename T, typename = m_void<>>
    struct m_has_resize : m_false {
    };
    template<typename T>
    struct m_has_resize<T, m_void<decltype(std::declval<T &>().resize(1U))>> : m_true {
    };

    // m_has_reserve
    template<typename T, typename = m_void<>>
    struct m_has_reserve : m_false {
    };
    template<typename T>
    struct m_has_reserve<T, m_void<decltype(std::declval<T &>().reserve(1U))>> : m_true {
    };

    auto m_composite_function() {
        return [](auto &&arg) -> decltype(auto) {
            return std::forward<decltype(arg)>(arg);
        };
    }

    template<typename Fn>
    auto m_composite_fun(Fn &&fn) {
        return [fn = std::forward<Fn>(fn)](auto &&... args) -> decltype(auto) {
            return fn(std::forward<decltype(args)>(args)...);
        };
    }

    template<typename Fn, typename... Fns>
    auto m_composite_fun(Fn &&fn, Fns &&... fns) {
        return [fn = std::forward<Fn>(fn), fns...](auto &&... args) -> decltype(auto) {
            return fn(m_composite_fun(std::move(fns)...)(std::forward<decltype(args)>(args)...));
        };
    }
}

#endif //MYTINYSTL_FUNCTION_H
