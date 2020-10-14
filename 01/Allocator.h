#include <cstdio>


class Allocator
{
    std::size_t size_ = 0, offset_ = 0;
    char *allotted_memory_;
    bool allocated_ = false;
public:
    ~Allocator();
    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
};
