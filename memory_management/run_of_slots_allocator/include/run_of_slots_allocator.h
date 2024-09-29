#ifndef MEMORY_MANAGEMENT_RUN_OF_SLOTS_ALLOCATOR_INCLUDE_RUN_OF_SLOTS_ALLOCATOR_H
#define MEMORY_MANAGEMENT_RUN_OF_SLOTS_ALLOCATOR_INCLUDE_RUN_OF_SLOTS_ALLOCATOR_H

#include <cstdint>
#include <cstddef>
#include "base/macros.h"

template <size_t ONE_MEM_POOL_SIZE, size_t... SLOTS_SIZES>
class RunOfSlotsAllocator {
    static_assert(sizeof...(SLOTS_SIZES) != 0, "you should set slots sizes");

    // here we recomend you to use class MemoryPool to create RunOfSlots for 1 size. Use new to allocate them from heap.
    // remember, you can not use any containers with heap allocations
    template <size_t MEM_POOL_SIZE, size_t SLOT_SIZE>
    class RunOfSlotsMemoryPool;

public:
    RunOfSlotsAllocator() = default;
    ~RunOfSlotsAllocator() = default;

    template <class T = uint8_t>
    T *Allocate()
    {
        // TODO: Add your implementation here...
        return nullptr;
    }

    void Free(void *ptr)
    {
        // TODO: Add your implementation here...
    }

    /**
     * @brief Method should check in @param ptr is pointer to mem from this allocator
     * @returns true if ptr is from this allocator
     */
    bool VerifyPtr([[maybe_unused]] void *ptr)  // TODO: remove [[maybe_unused]]
    {
        // TODO: Add your implementation here...
        return false;
    }

private:
    // TODO: Add your fields and methods here...
};

#endif  // MEMORY_MANAGEMENT_RUN_OF_SLOTS_ALLOCATOR_INCLUDE_RUN_OF_SLOTS_ALLOCATOR_H