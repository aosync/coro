#include "coro.hpp"

#include <stdio.h>

namespace coro {
    CoroException::CoroException(char const *msg) : msg(msg) {}
    char const *CoroException::what() const throw() {
        return msg;
    }
    thread_local Coro *Coro::m_current = nullptr;
    void Coro::call() {
        try {
            m_func();
        } catch (std::exception &e) {
            
        }
    }
    void Coro::wrap(Coro *g) {
        std::invoke(&Coro::call, g);
    }
    void Coro::bind() {
        ctx_link_to(m_ctx, m_stack.end_aligned(8), (void (*)(void*))wrap, this);
    }
    Coro::Coro(std::function<void()>&& func) : m_stack(8), m_func(std::move(func)) {
        m_link = ctx_create();
        if (m_link == nullptr)
            throw CoroException("coro: link context allocation failed");
        m_ctx = ctx_create();
        if (m_ctx == nullptr) {
            ctx_destroy(m_link);
            throw CoroException("coro: context allocation failed");
        }

        bind();
    }
    Coro::~Coro() {
        ctx_destroy(m_ctx);
        ctx_destroy(m_link);
    }
    void Coro::rebind(std::function<void()>&& func) {
        if (m_active)
            throw CoroException("coro: cannot rebind an active coroutine");

        std::swap(func, m_func);

        bind();
    }
    void Coro::resume() {
        if (m_running)
            return;
        
        Coro *prev = Coro::m_current;
        m_active = true;

        m_status = REBIND;
        m_running = true;
        Coro::m_current = this;
        ctx_switch(m_link, m_ctx);
        Coro::m_current = prev;
        m_running = false;

        if (m_status == REBIND) {
            m_active = false;
            bind();
        }
    }
    void Coro::yield() {
        if (!Coro::m_current)
            throw CoroException("coro: cannot yield: not in a coroutine context");

        m_status = LAISSEZ;
        ctx_switch(m_ctx, m_link);
    }

    Coro *Coro::current() {
        return Coro::m_current;
    }

    void yield() {
        Coro *c = coro::Coro::current();
        if(!c)
            throw CoroException("coro: cannot yield: not in a coroutine context");
        
        c->yield();
    }
}