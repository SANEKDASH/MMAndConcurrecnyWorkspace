#include <gtest/gtest.h>
#include "memory_management/reference_counting_gc/include/object_module.h"

TEST(ReferenceCountingGC, DefaultObjectUsage)
{
    Object<size_t> obj;
}