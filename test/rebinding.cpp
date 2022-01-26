#include <coro.hpp>

int i = 0;

int main() {
    coro::Coro c([] {
        i = 5;
    });

    c.resume();

    c.rebind([] {
        i = 42;
    });

    c.resume();
    
    return i != 42;
}