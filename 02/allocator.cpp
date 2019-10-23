#include <cstdlib>

class LinearAllocator
{
public:
    LinearAllocator(size_t maxSize) {
        buf = static_cast<char *> (std::malloc(maxSize));
        cur_ptr = buf;
        max_size = maxSize;
    }
    char* alloc(size_t size) {
        if (cur_ptr + size > buf + max_size) {
            return nullptr;
        }
        char *old_ptr = cur_ptr;
        cur_ptr += size;
        return old_ptr;
    }
    void reset() {
        cur_ptr = buf;
    }
    ~LinearAllocator() {
        std::free(buf);
    }
private:
    char* buf;
    char* cur_ptr;
    size_t max_size;
};
