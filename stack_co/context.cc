//
// Created by Jasonkay on 2022/6/5.
//

#include "context.h"

extern "C" {
extern void switch_context(stack_co::Context *, stack_co::Context *) asm("switch_context");
}

namespace stack_co {

    void Context::switch_from(Context *previous) {
        switch_context(previous, this);
    }

    void Context::prepare(Context::Callback ret, Context::Word rdi) {
        Word sp = get_stack_pointer();
        fill_registers(sp, ret, rdi);
    }

    bool Context::test() {
        char current;
        ptrdiff_t diff = std::distance(std::begin(_stack), &current);
        return diff >= 0 && diff < STACK_SIZE;
    }

    Context::Word Context::get_stack_pointer() {
        auto sp = std::end(_stack) - sizeof(Word);
        sp = decltype(sp)(reinterpret_cast<size_t>(sp) & (~0xF));
        return sp;
    }

    void Context::fill_registers(Word sp, Callback ret, Word rdi, ...) {
        ::memset(_registers, 0, sizeof _registers);
        auto pRet = (Word *) sp;
        *pRet = (Word) ret;
        _registers[RSP] = sp;
        _registers[RET] = *pRet;
        _registers[RDI] = rdi;
    }

} // namespace stack_co
