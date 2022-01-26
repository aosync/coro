#include <coro.hpp>

int main() {
    try {
        coro::yield();
        return 1;
    } catch (std::exception &e) {
        return 0;
    }
}