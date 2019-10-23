#include <iostream>
#include "allocator.h"
#include <cstdlib>

int main() {
    char *p, *q;
    bool no_errors = 1;
    LinearAllocator all = LinearAllocator(5);
    if (!(p = all.alloc(3)) || all.alloc(3)) {
        no_errors = 0;
        std::cout << "error on test 1" << std::endl;
    }
    all.reset();
    if (!(q = all.alloc(3)) || !all.alloc(2)) {
        no_errors = 0;
        std::cout << "error on test 2" << std::endl;
    }
    if (q != p) {
        no_errors = 0;
        std::cout << "error on test 3" << std::endl;
    }
    all = LinearAllocator(100);
    for (int i = 0; i < 100; i++) {
        if (!(all.alloc(1))) {
            no_errors = 0;
            std::cout << "error on test 4" << std::endl;
        }
    }
    if (all.alloc(1)) {
        no_errors = 0;
        std::cout << "error on test 5" << std::endl;
    }
    if (no_errors) {
        std::cout << "no errors" << std::endl;
    }
}
