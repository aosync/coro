#include "stack.hpp"

#ifdef __WIN32
#include <windows.h>
#else
#include <sys/mman.h>
#include <unistd.h>
#endif

#include <errno.h>
#include <stdio.h>

static size_t get_pages_to_length(size_t pages) {
#ifdef __WIN32
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    return si.dwPageSize * pages;
#else
    return sysconf(_SC_PAGESIZE) * pages;
#endif
}

namespace coro {
    Stack::Stack(size_t pages) : m_pages(pages) {
        m_length = get_pages_to_length(m_pages);
#ifdef __WIN32
        m_start = new char[m_length];
#else
        m_start = (char*)mmap(NULL, m_length, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE|MAP_STACK, -1, 0);
        if (m_start == MAP_FAILED)
            throw "stack allocation failed";
#endif
    }
    Stack::~Stack() {
        if (!m_start)
            return;

#ifdef __WIN32
        delete[] m_start;
#else
        munmap(m_start, m_length);
#endif
    }
    Stack::Stack(Stack &&other) {
        m_start = other.m_start;
        m_pages = other.m_pages;
        m_length = other.m_length;

        other.m_start = nullptr;
    }
    char *Stack::start() {
        return m_start;
    }
    char *Stack::end() {
        return m_start + m_length;
    }
    char *Stack::end_aligned(size_t alignment) {
        return (char*)((size_t)end() & ~alignment);
    }
    size_t Stack::pages() {
        return m_pages;
    }
    size_t Stack::length() {
        return m_length;
    }
}