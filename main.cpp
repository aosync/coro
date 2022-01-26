
extern "C" {
#include <ctx.h>
}

#include <stdio.h>
#include <stack.hpp>
#include <coro.hpp>
#include <vector>
#include <utility>
#include <memory>

void second() {
    printf("second\n");
}

void first(int i) {
    printf("first %d\n", i);          // does not print
}

void use_stack(coro::Stack lol) {
    printf("stack vibing\n");
}

int main() {
    coro::Coro gthr([] {
        coro::Coro::current()->resume();
        int *i = new int(54);
        coro::yield();
        delete i;
    });

    gthr.resume();
    gthr.resume();
    return 0;
}