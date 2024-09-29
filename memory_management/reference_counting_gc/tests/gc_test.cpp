#include <gtest/gtest.h>
#include "memory_management/reference_counting_gc/include/object_module.h"

class Return42 {
public:
    size_t get() const
    {
        return 42U;
    }
};

TEST(ReferenceCountingGC, SinglePtrUsage)
{
    Object<size_t> obj;
    ASSERT_EQ(obj.use_count(), 0);
    ASSERT_EQ(obj.get(), nullptr);

    constexpr size_t VALUE_TO_CREATE = 42U;
    Object<size_t> sizeObj = MakeObject<size_t>(VALUE_TO_CREATE);
    ASSERT_EQ(sizeObj.use_count(), 1U);
    ASSERT_NE(sizeObj.get(), nullptr);
    ASSERT_EQ(*sizeObj, VALUE_TO_CREATE);

    Object<Return42> classObj = MakeObject<Return42>();
    ASSERT_EQ(classObj.use_count(), 1U);
    ASSERT_NE(classObj.get(), nullptr);
    ASSERT_EQ(classObj->get(), Return42().get());
}

TEST(ReferenceCountingGC, CopySemanticUsage)
{
    constexpr size_t VALUE_TO_CREATE = 42U;
    Object<size_t> obj1 = MakeObject<size_t>(VALUE_TO_CREATE);
    {
        Object<size_t> obj2(obj1);
        ASSERT_EQ(obj1.use_count(), 2U);
        ASSERT_EQ(obj1.get(), obj2.get());
    }
    ASSERT_EQ(obj1.use_count(), 1U);
    {
        Object<size_t> obj2;
        obj2 = obj1;
        ASSERT_EQ(obj1.use_count(), 2U);
        ASSERT_EQ(obj1.get(), obj2.get());
    }
    ASSERT_EQ(obj1.use_count(), 1U);
}

TEST(ReferenceCountingGC, MoveSemanticUsage)
{
    constexpr size_t VALUE_TO_CREATE = 42U;
    Object<size_t> obj1 = MakeObject<size_t>(VALUE_TO_CREATE);
    size_t *ptr = obj1.get();
    {
        Object<size_t> obj2(std::move(obj1));
        ASSERT_EQ(obj2.use_count(), 1U);
        ASSERT_EQ(obj2.get(), ptr);
        ASSERT_EQ(obj1.use_count(), 0);
        ASSERT_EQ(obj1.get(), nullptr);
        obj1 = obj2;
    }
    ASSERT_EQ(obj1.use_count(), 1U);
    {
        Object<size_t> obj2;
        obj2 = std::move(obj1);
        ASSERT_EQ(obj2.use_count(), 1U);
        ASSERT_EQ(obj2.get(), ptr);
        ASSERT_EQ(obj1.use_count(), 0);
        ASSERT_EQ(obj1.get(), nullptr);
        obj1 = obj2;
    }
    ASSERT_EQ(obj1.use_count(), 1U);
}

TEST(ReferenceCountingGC, GcDeletingTest) {}