//
// Created by Jasonkay on 2022/6/5.
//

#ifndef COROUTINE_STATUS_H
#define COROUTINE_STATUS_H

namespace stack_co {

    // The status of the coroutine
    struct Status {
        using Bitmask = unsigned char;

        constexpr static Bitmask MAIN = 1 << 0;
        constexpr static Bitmask IDLE = 1 << 1;
        constexpr static Bitmask RUNNING = 1 << 2;
        constexpr static Bitmask EXIT = 1 << 3;

        Bitmask operator&(Bitmask mask) const { return flag & mask; }

        Bitmask operator|(Bitmask mask) const { return flag | mask; }

        Bitmask operator^(Bitmask mask) const { return flag ^ mask; }

        void operator&=(Bitmask mask) { flag &= mask; }

        void operator|=(Bitmask mask) { flag |= mask; }

        void operator^=(Bitmask mask) { flag ^= mask; }

        Bitmask flag;
    };


} // namespace stack_co

#endif //COROUTINE_STATUS_H
