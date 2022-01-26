#include <coro.hpp>

int test = 10;

int main() {
    coro::Coro c([] {
        coro::Coro::current()->resume();
        test = 1;
    });
    
    c.resume();
    
    return test != 1;
}