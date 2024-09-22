#ifndef ALLOCATOR_INCLUDE_ALLOCATOR
#define ALLOCATOR_INCLUDE_ALLOCATOR

#include <cstddef>  // is used for size_t

class AllocatorIface {
public:
    // Default interface
    virtual void *Allocate(size_t size) = 0;
    virtual void Deallocate(void *ptr) = 0;
};

#endif  // ALLOCATOR_INCLUDE_ALLOCATOR