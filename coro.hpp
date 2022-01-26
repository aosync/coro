#pragma once

#define CORO_PAGES 9

#include <functional>
#include <thread>

extern "C" {
    #include <ctx.h>
}

#include "stack.hpp"

namespace coro {
    struct CoroException : std::exception {
        char const *msg;
        CoroException(char const *msg);
        char const *what() const throw();
    };

    enum CoroStatus {
        REBIND,
        LAISSEZ
    };

    class Coro {
        bool m_active = false;
        bool m_running = false;
        Stack m_stack;
        std::function<void()> m_func;
        ctx m_ctx;
        CoroStatus m_status;

        static thread_local Coro *m_current;

        static void wrap2(Coro *g);
        void wrap();
        void bind();
    public:
        Coro(std::function<void()>&& func);
        void rebind(std::function<void()>&& func);
        void resume();
        void yield();
        static Coro *current();
    };

    void yield();
}