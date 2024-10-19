#ifndef MEMORY_MANAGEMENT_REFERECNCE_COUNTING_OBJECT_MODLE_INCLUDE_OBJECT_MODLE_H
#define MEMORY_MANAGEMENT_REFERECNCE_COUNTING_OBJECT_MODLE_INCLUDE_OBJECT_MODLE_H

#include <cstddef>
#include <utility>

struct DataHeader
{
    size_t refCount;
};

template <class T>
class Object;

template <class T, class... Args>
static Object<T> MakeObject([[maybe_unused]] Args... args)
{
    char *objPtr = new char [sizeof(DataHeader) + sizeof(T)];

// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    T *val = new (objPtr + sizeof(DataHeader)) T{args...};

//NOLINTNEXTLINE(cppcoreguidelines-pro-type-cstyle-cast)
    ((DataHeader *) (objPtr))->refCount = 1;

    Object<T> newObj{objPtr};

    return newObj;
}

// TODO(you): Implement object base on java object representatoin
template <class T>
class Object {
public:

    Object() = default;

    explicit Object(char *objPtr)
    {
        obj_    = objPtr;

        SetPointers();
    }

    explicit Object(std::nullptr_t) {}

    ~Object()
    {
        Release();
    }

    // copy semantic
    Object([[maybe_unused]] const Object<T> &other)
    {
        obj_    = other.obj_;
        val_    = other.val_;
        header_ = other.header_;

        if (obj_ != nullptr)
        {
            ++(header_->refCount);
        }
    }
    // NOLINTNEXTLINE(bugprone-unhandled-self-assignment)
    Object<T> &operator=([[maybe_unused]] const Object<T> &other)
    {
        Release();

        obj_    = other.obj_;
        val_    = other.val_;
        header_ = other.header_;

        if (obj_ != nullptr)
        {
            ++(header_->refCount);
        }

        return *this;
    }

    // move semantic
    Object([[maybe_unused]] Object<T> &&other)
    {
        obj_ = std::move(other.obj_);

        SetPointers();

        other.obj_    = nullptr;
        other.val_    = nullptr;
        other.header_ = nullptr;
    }
    Object<T> &operator=([[maybe_unused]] Object<T> &&other)
    {
        Release();

        obj_ = std::move(other.obj_);

        SetPointers();

        other.obj_    = nullptr;
        other.val_    = nullptr;
        other.header_ = nullptr;

        return *this;
    }

    // member access operators
    T &operator*() const noexcept
    {
        return *val_;
    }

    T *operator->() const noexcept
    {
        return val_;
    }

    size_t UseCount() const
    {
        if (obj_ != nullptr)
        {
            // NOLINTNEXTLINE(clang-analyzer-cplusplus.NewDelete)
            return header_->refCount;
        }

        return 0;
    }

    bool operator==([[maybe_unused]] const Object<T> other) const
    {
        return val_ == other.val_;
    }

    bool operator!=(const Object<T> other) const
    {
        return !(*this == other);
    }

    bool operator==(std::nullptr_t) const
    {
        return val_ == nullptr;
    }

    bool operator!=(std::nullptr_t) const
    {
        return val_ != nullptr;
    }

private:
    void SetPointers()
    {
        header_ = (DataHeader *) obj_;
// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        val_    = (T *) (obj_ + sizeof(DataHeader));
    }

    void Release()
    {
        if (obj_ != nullptr)
        {
            if (--(header_->refCount) == 0)
            {
                val_->~T();

                delete []obj_;

                val_    = nullptr;
                header_ = nullptr;
            }
        }
    }

    char *obj_ = nullptr;

    T *val_ = nullptr;

    DataHeader *header_ = nullptr;
};

#endif  // MEMORY_MANAGEMENT_REFERECNCE_COUNTING_GC_INCLUDE_OBJECT_MODLE_H
