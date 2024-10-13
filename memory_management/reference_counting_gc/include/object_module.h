#ifndef MEMORY_MANAGEMENT_REFERECNCE_COUNTING_GC_INCLUDE_OBJECT_MODEL_H
#define MEMORY_MANAGEMENT_REFERECNCE_COUNTING_GC_INCLUDE_OBJECT_MODEL_H

#include <cstddef>
#include <utility>

template <class T>
class Object;

template <class T, class... Args>
static Object<T> MakeObject([[maybe_unused]] Args... args)
{
    return static_cast<Object<T>>(new T{args...});
}

template <class T>
class Object {
public:
    Object() = default;
    explicit Object(std::nullptr_t) {}
    explicit Object([[maybe_unused]] T *ptr)
    {
        val_ = ptr;

        dataHeader_ = new DataHeader;

        dataHeader_->refCount = 1;
    }

    ~Object()
    {
        if (dataHeader_ != nullptr)
        {
            //NOLINTNEXTLINE(clang-analyzer-cplusplus.NewDelete)
            --dataHeader_->refCount;

            if (dataHeader_->refCount == 0)
            {
                delete dataHeader_;
                delete val_;

                dataHeader_ = nullptr;
                val_        = nullptr;
            }
        }
    }

    // copy semantic
    Object([[maybe_unused]] const Object<T> &other)
    {
        val_ = other.val_;

        dataHeader_ = other.dataHeader_;

        ++dataHeader_->refCount;
    }
    // NOLINTNEXTLINE(bugprone-unhandled-self-assignment)
    Object<T> &operator=([[maybe_unused]] const Object<T> &other)
    {
        val_ = other.val_;

        if (other.dataHeader_ != nullptr)
        {
            dataHeader_ = other.dataHeader_;

            ++dataHeader_->refCount;
        }

        return *this;
    }

    // move semantic
    Object([[maybe_unused]] Object<T> &&other)
    {
        delete val_;
        delete dataHeader_;

        val_        = std::move(other.val_);
        dataHeader_ = std::move(other.dataHeader_);

        other.val_        = nullptr;
        other.dataHeader_ = nullptr;

    }
    Object<T> &operator=([[maybe_unused]] Object<T> &&other)
    {
        delete val_;
        delete dataHeader_;

        val_        = std::move(other.val_);
        dataHeader_ = std::move(other.dataHeader_);

        other.val_        = nullptr;
        other.dataHeader_ = nullptr;

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
        if (dataHeader_ != nullptr)
        {
            // NOLINTNEXTLINE(clang-analyzer-cplusplus.NewDelete)
            return dataHeader_->refCount;
        }

        return 0;
    }

private:
    struct DataHeader
    {
        size_t refCount = 0;
    };

    T *val_ = nullptr; // this field can be deleted

    DataHeader *dataHeader_ = nullptr;
};

#endif  // MEMORY_MANAGEMENT_REFERECNCE_COUNTING_GC_INCLUDE_OBJECT_MODEL_H
