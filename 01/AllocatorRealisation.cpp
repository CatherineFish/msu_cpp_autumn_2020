#include "Allocator.h"


void Allocator::makeAllocator(size_t maxSize)
{
	if (allocated_)
    {
	    return;
    }
    allotted_memory_ = new char [maxSize];
    allocated_ = true;
    size_ = maxSize;
    offset_ = 0;
    return;
}


char * Allocator::alloc(size_t size)
{
    if (size_ - offset_ >=  size && allocated_)
    {
        offset_ += size;
        return allotted_memory_ + (offset_ - size);
    }
    return nullptr;
}


void Allocator::reset()
{
    offset_ = 0;
    return;
}


Allocator::~Allocator()
{
    if (allocated_)
    {
	    delete[] allotted_memory_; 
    }
}
