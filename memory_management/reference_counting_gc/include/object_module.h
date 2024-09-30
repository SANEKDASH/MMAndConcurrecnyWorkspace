#ifndef MEMORY_MANAGEMENT_REFERECNCE_COUNTING_GC_INCLUDE_OBJECT_MODEL_H
#define MEMORY_MANAGEMENT_REFERECNCE_COUNTING_GC_INCLUDE_OBJECT_MODEL_H

#include <cstddef>

template <class T>
class Object;

template <class T, class... Args>
static Object<T> MakeObject([[maybe_unused]] Args... args)
{
    // TODO(you): Implemet this finction
    return {};
}

template <class T>
class Object {
public:
    Object() = default;
    explicit Object(std::nullptr_t) {}
    explicit Object([[maybe_unused]] T *ptr) {}

    ~Object() = default; // this method should be changed

    // copy semantic
    Object([[maybe_unused]] const Object<T> &other) {}
    // NOLINTNEXTLINE(bugprone-unhandled-self-assignment)
    Object<T> &operator=([[maybe_unused]] const Object<T> &other)
    {
        return *this;
    }

    // move semantic
    Object([[maybe_unused]] Object<T> &&other) {}
    Object<T> &operator=([[maybe_unused]] Object<T> &&other)
    {
        return *this;
    }

    // member access operators
    T &operator*() const noexcept {
        return *val_;
    }

    T *operator->() const noexcept {
        return val_;
    }

    // internal access
    void Reset([[maybe_unused]] T *ptr) {}
    T *Get() const
    {
        return val_;
    }
    size_t UseCount() const
    {
        return 0;
    }

private:
    // TODO(you): Add your fields and methods here...
    T* val_ = nullptr; // this field can be deleted
};

#endif  // MEMORY_MANAGEMENT_REFERECNCE_COUNTING_GC_INCLUDE_OBJECT_MODEL_H