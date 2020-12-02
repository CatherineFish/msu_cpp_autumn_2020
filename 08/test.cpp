#include <iostream>

#include <cassert>

#include "ThreadPool.h"


struct A {};

void foo(const A & ) {}

auto odd(size_t n) {
    return n * n;
}

auto even(size_t n) {
    return n / 2;
}

void DefaultTest(void) {
    ThreadPool pool(8);
    auto task1 = pool.exec(foo, A());
    task1.get();

    auto task2 = pool.exec([]() {
        return 1;
    });
    int res = task2.get();
    assert(res == 1);
    return;
}

void OneMoreTest() {
    ThreadPool pool(16);
    for (size_t i = 0; i < 16; i++) {
        if (i % 2) {
            auto cur_task = pool.exec(odd, i);
            assert(cur_task.get() == i * i);
        } else {
            auto cur_task = pool.exec(even, i);
            assert(cur_task.get() == i / 2);
        }
    }
}

int main(void) {
    DefaultTest();
    OneMoreTest();
    std::cout << "Success!\n";
    return 0;
}