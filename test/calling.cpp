#include <coro.hpp>

int test = 1;

int main() {
    coro::Coro c([] {
        test = 0;
    });

    c.resume();
    
    return test;
}