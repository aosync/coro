#include <coro.hpp>

int i = 0;

int main() {
    coro::Coro c([] {
        i = 5;
        coro::yield();
        i = 10;
    });

    c.resume();

    try {
        c.rebind([] {
            i = 42;
        });
        return 1;
    } catch (std::exception &e) {
        return 0;
    }
}