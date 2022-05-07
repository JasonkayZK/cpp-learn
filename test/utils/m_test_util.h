//
// Created by kylinkzhang on 2022.05.06.
//

#ifndef MYTINYSTL_M_TEST_UTIL_H
#define MYTINYSTL_M_TEST_UTIL_H

#include <ctime>
#include <algorithm>

namespace mytinystl_utils {

    template<typename T>
    struct calculate_time_t {
        T _data;
        double _time_ms;
        double _time_s;

        calculate_time_t(const T &data, const double time_ms, const double time_s)
        noexcept: _data(data), _time_ms(time_ms), _time_s(time_s) {};
    };

    template<typename Fn, typename... Args>
    auto calculate_time(Fn &fn, Args &&... args) {
        time_t t1 = clock();
        fn(std::forward<Args>(args)...);
        time_t t2 = clock();

        return calculate_time_t<decltype(0)>
                {
                        0,
                        static_cast<double>(t2) - static_cast<double>(t1),
                        (static_cast<double>(t2) - static_cast<double>(t1)) / CLOCKS_PER_SEC
                };
    }

    template<typename Fn, typename... Args>
    auto calculate_time_with_return(Fn &fn, Args &&... args) {
        time_t t1 = clock();
        auto _tmp = fn(std::forward<Args>(args)...);
        time_t t2 = clock();
        return calculate_time_t<decltype(_tmp)>
                (
                        _tmp,
                        static_cast<double>(t2) - static_cast<double>(t1),
                        (static_cast<double>(t2) - static_cast<double>(t1)) / CLOCKS_PER_SEC
                );
    }

}

#endif //MYTINYSTL_M_TEST_UTIL_H
