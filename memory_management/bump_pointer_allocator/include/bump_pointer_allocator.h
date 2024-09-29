#ifndef MEMORY_MANAGEMENT_BUMP_POINTER_ALLOCATOR_INCLUDE_BUMP_POINTER_ALLOCATOR_H
#define MEMORY_MANAGEMENT_BUMP_POINTER_ALLOCATOR_INCLUDE_BUMP_POINTER_ALLOCATOR_H

#include <cstddef>  // is used for size_t
#include <cstdint>
#include "base/macros.h"

template <size_t MEMORY_POOL_SIZE>
class BumpPointerAllocator {
public:
    BumpPointerAllocator() = default;
    ~BumpPointerAllocator() = default;
    NO_COPY_SEMANTIC(BumpPointerAllocator);
    NO_MOVE_SEMANTIC(BumpPointerAllocator);

    template <class T = uint8_t>
    T *Allocate([[maybe_unused]] size_t count)  // TODO(you): remove [[maybe_unused]]
    {
        // TODO(you): Add your implementation here...
        return nullptr;
    }

    void Free()
    {
        // TODO(you): Add your implementation here...
    }

    /**
     * @brief Method should check in @param ptr is pointer to mem from this allocator
     * @returns true if ptr is from this allocator
     */
    bool VerifyPtr([[maybe_unused]] void *ptr)  // TODO(you): remove [[maybe_unused]]
    {
        // TODO(you): Add your implementation here...
        return false;
    }

private:
    // TODO(you): Add your fields and methods here...
};

#endif  // MEMORY_MANAGEMENT_BUMP_POINTER_ALLOCATOR_INCLUDE_BUMP_POINTER_ALLOCATOR_H