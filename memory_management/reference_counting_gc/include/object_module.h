#ifndef MEMORY_MANAGEMENT_REFERECNCE_COUNTING_GC_INCLUDE_OBJECT_MODEL_H
#define MEMORY_MANAGEMENT_REFERECNCE_COUNTING_GC_INCLUDE_OBJECT_MODEL_H

#include <cstddef>

template <class T>
class Object;

template <class T, class... Args>
static Object<T> MakeObject(Args... args)
{
    // TODO(you): Implemet this finction
    return {};
}

template <class T>
class Object {
public:
    Object() = default;
    Object([[maybe_unused]] T *ptr) {}

    ~Object() {}

    // copy semantic
    Object([[maybe_unused]] Object<T> &other) {}
    Object<T> &operator=([[maybe_unused]] Object<T> &other)
    {
        return {};
    }

    // move semantic
    Object([[maybe_unused]] Object<T> &&other) {}
    Object<T> &operator=([[maybe_unused]] Object<T> &&other)
    {
        return {};
    }

    // member access operators
    T &operator*() const noexcept {}
    T *operator->() const noexcept {}

    // internal access
    void reset([[maybe_unused]] T *ptr) noexcept {}
    T *get() const noexcept
    {
        return nullptr;
    }
    size_t use_count() const noexcept
    {
        return 0;
    }

private:
    // TODO(you): Add your fields and methods here...
};

#endif  // MEMORY_MANAGEMENT_REFERECNCE_COUNTING_GC_INCLUDE_OBJECT_MODEL_H