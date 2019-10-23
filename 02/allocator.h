#pragma ones

class LinearAllocator
{
public:
    LinearAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
    ~LinearAllocator();
private:
    char* buf;
    char* cur_ptr;
    size_t max_size;
};
