//
// Created by kylinkzhang on 2022.05.06.
//

#ifndef MYTINYSTL_M_LOG_H
#define MYTINYSTL_M_LOG_H

#include <fstream>
#include <time.h>

// Log path
#define LOG_PATH "log.txt"

// Concurrency log
#define CONCURRENCY_LOGGER 1

#ifdef CONCURRENCY_LOGGER

#include <mutex>

std::mutex log_mutex;
#endif

namespace mytinystl_utils {

    constexpr const int ERROR_FILE_OPEN = 1;

    template<typename T>
    void _m_log(std::ofstream &logger, T t) {
        log << t;
    }

    template<typename T, typename... Args>
    void _m_log(std::ofstream &logger, T t, Args... args) {
        log << t;
        _m_log(logger, args...);
    }

    template<typename... Args>
    int m_log(Args... args) {

#ifdef CONCURRENCY_LOGGER
        std::lock_guard<std::mutex> lock(log_mutex);
#endif

        std::ofstream log(LOG_PATH, std::ios::app);
        if (!log.is_open()) {
            return ERROR_FILE_OPEN;
        }

        std::time_t cur;
        time(&cur);
        log << std::endl << std::ctime(&cur);

        _m_log(log, args...);

        log << std::endl;
        log.close();
        return 0;
    }

}

#endif //MYTINYSTL_M_LOG_H
