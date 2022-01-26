#include <coro.hpp>

int test = 10;

int main() {
    coro::Coro c([] {
        test = 0;
        test++;
        coro::yield();
        test++;
    });

    c.resume();
    c.resume();
    c.resume();
    
    return test != 1;
}