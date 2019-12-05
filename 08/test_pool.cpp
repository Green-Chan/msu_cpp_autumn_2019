#include "thread_pool.h"

#include <iostream>

using namespace std;

int main() {
    struct A {};

    void foo(const A&) {}

    ThreadPool pool(8);

    auto task1 = pool.exec(foo, A());
    task1.get();

    auto task2 = pool.exec([]() { return 1; });
    task2.get();
}
