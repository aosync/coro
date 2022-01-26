#pragma once

#include <cstddef>

namespace coro {
    // Stack: cross platform coroutine stack container and allocation.
    class Stack {
        char *m_start;
        size_t m_pages;
        size_t m_length;
    public:
        Stack(size_t pages);
        Stack(Stack& other) = delete;
        Stack(Stack&& other);
        ~Stack();
        char *start();
        char *end();
        char *end_aligned(size_t alignment);
        size_t pages();
        size_t length();
    };
}