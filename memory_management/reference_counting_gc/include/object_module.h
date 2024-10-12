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
        data_header_ = new DataHeader;
        data_header_->ref_count = 1;
    }

    ~Object()
    {
        if (data_header_ != nullptr)
        {
            --data_header_->ref_count;

            if (data_header_->ref_count == 0)
            {
                delete data_header_;
                delete val_;
            }
        }
    }

    // copy semantic
    Object([[maybe_unused]] const Object<T> &other)
    {
        val_ = other.val_;

        data_header_ = other.data_header_;

        ++data_header_->ref_count;
    }
    // NOLINTNEXTLINE(bugprone-unhandled-self-assignment)
    Object<T> &operator=([[maybe_unused]] const Object<T> &other)
    {
        val_ = other.val_;

        if (other.data_header_ != nullptr)
        {
            data_header_ = other.data_header_;

            ++data_header_->ref_count;
        }

        return *this;
    }

    // move semantic
    Object([[maybe_unused]] Object<T> &&other)
    {
        delete val_;
        delete data_header_;

        val_         = std::move(other.val_);
        data_header_ = std::move(other.data_header_);

        other.val_         = nullptr;
        other.data_header_ = nullptr;

    }
    Object<T> &operator=([[maybe_unused]] Object<T> &&other)
    {
        delete val_;
        delete data_header_;

        val_         = std::move(other.val_);
        data_header_ = std::move(other.data_header_);

        other.val_         = nullptr;
        other.data_header_ = nullptr;

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
        if (data_header_ != nullptr)
        {
            return data_header_->ref_count;
        }

        return 0;
    }

private:
    struct DataHeader
    {
        size_t ref_count = 0;
    };

    T *val_ = nullptr; // this field can be deleted

    DataHeader *data_header_ = nullptr;
};

#endif  // MEMORY_MANAGEMENT_REFERECNCE_COUNTING_GC_INCLUDE_OBJECT_MODEL_H
