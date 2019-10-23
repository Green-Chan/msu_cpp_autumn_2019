#include <cstdlib>
#include "allocator.h"

LinearAllocator::LinearAllocator(size_t maxSize) {
    buf = static_cast<char *> (std::malloc(maxSize));
    cur_ptr = buf;
    max_size = maxSize;
}

char *LinearAllocator::alloc(size_t size) {
    if (cur_ptr + size > buf + max_size) {
        return nullptr;
    }
    char *old_ptr = cur_ptr;
    cur_ptr += size;
    return old_ptr;
}

void LinearAllocator::reset() {
    cur_ptr = buf;
}

LinearAllocator::~LinearAllocator() {
    std::free(buf);
}
