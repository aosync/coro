#include <coro.hpp>

int test = 10;

int main() {
    coro::Coro c([] {
        test = 0;
        coro::Coro h([] {
            test = 1;
        });
        h.resume();
    });

    c.resume();
    
    return test != 1;
}