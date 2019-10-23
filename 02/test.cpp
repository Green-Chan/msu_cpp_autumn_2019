#include <iostream>
#include "allocator.h"

int main() {
    char *p;
    {
    LinearAllocator all = LinearAllocator(5);
    p = all.alloc(3);
    std::cout << (int) p << std::endl;
    std::cout << (int) all.alloc(3) << std::endl;
    all.reset();
    std::cout << (int) all.alloc(3) << std::endl;
    std::cout << (int) all.alloc(2) << std::endl;
    all.reset();
    }
    std::cout << *p;
}
