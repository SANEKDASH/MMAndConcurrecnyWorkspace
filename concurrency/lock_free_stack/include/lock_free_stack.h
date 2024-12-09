#ifndef CONCURRENCY_LOCK_FREE_STACK_CONTAINERS_INCLUDE_LOCK_FREE_STACK_H
#define CONCURRENCY_LOCK_FREE_STACK_CONTAINERS_INCLUDE_LOCK_FREE_STACK_H

#include <optional>
#include <stdio.h>
#include <atomic>

const size_t MAX_HAZARDS_COUNT = 20;

template<class T>
struct StackNode {
    T data;
    StackNode *prev;

    StackNode(T val, StackNode *newPrev) : data(val), prev(newPrev) {}
};

template<class T>
class LockFreeStack {
// =================== LOCK FREE STACK METHODS ===================
public:
    void Push([[maybe_unused]] T val) {
        StackNode<T> *newNode = new StackNode<T> {val, nullptr};

        while (true) {
            newNode->prev = head.load(std::memory_order_acquire);

            if (head.compare_exchange_weak(newNode->prev, newNode, std::memory_order_release)) {
                break;
            }
        }
    }

    std::optional<T> Pop() {
        std::atomic<StackNode<T> *> &hazPtr = hazardPointers_.GetHazardPointerForCurThread();

        StackNode<T> *oldHead = nullptr;

        T valueToReturn;

        do {
            oldHead = head.load(std::memory_order_acquire);

            if (oldHead == nullptr) {
                hazPtr.store(nullptr);

                return std::nullopt;
            }

            StackNode<T> *tmp = nullptr;
            do {
                tmp = oldHead;

                hazPtr.store(oldHead);

                oldHead = head.load();
            } while (oldHead != tmp);

            valueToReturn = oldHead->data;

            if (head.compare_exchange_weak(oldHead, oldHead->prev, std::memory_order_release)) {
                break;
            }
        } while (true);

        hazPtr.store(oldHead);

        if (oldHead) {
            if (hazardPointers_.IsHazard(oldHead)) {
                DeleteLater(oldHead);
            }
            else {
                delete oldHead;
            }

            DeleteRetired();
        }

        return valueToReturn;
    }

    bool IsEmpty() {
        return head == nullptr;
    }

// =================== HAZARD POINTERS STRUCTS AND METHODS ===================

    struct HazardPtr {
        std::atomic<std::thread::id> ownerId;
        std::atomic<StackNode<T> *> ptr;
    };

    class HazardPointers {
    public:
        std::atomic<StackNode<T> *> &GetHazardPointerForCurThread() {
            thread_local static HazardPointerOwner hPtrOwner;

            return hPtrOwner.GetHazardPtr();
        }

        bool IsHazard(StackNode<T> *ptr) {
            for (int i = 0; i < MAX_HAZARDS_COUNT; i++) {
                if (hazardPointersArray[i].ptr.load() == ptr) {
                    return true;
                }
            }

            return false;
        }

    private:
        class HazardPointerOwner {
        public:
            HazardPointerOwner() : hPtr_(nullptr) {
                for (int i = 0; i < MAX_HAZARDS_COUNT; i++) {
                    std::thread::id oldId;

                    if (hazardPointersArray[i].ownerId.compare_exchange_strong(oldId, std::this_thread::get_id())) {
                        hPtr_ = &hazardPointersArray[i];
                        break;
                    }
                }
            }

            std::atomic<StackNode<T> *> &GetHazardPtr() {
                return hPtr_->ptr;
            }

            ~HazardPointerOwner() {
                hPtr_->ptr.store(nullptr);
                hPtr_->ownerId.store(std::thread::id());
            }

        private:
            HazardPtr *hPtr_;
        };

        static HazardPtr hazardPointersArray[MAX_HAZARDS_COUNT];
    };
private:

// =================== RETIRED POINTERS STRUCTS AND METHODS ===================

struct RetiredPointer {
    StackNode<T> *ptr;

    RetiredPointer *prev;

    RetiredPointer(StackNode<T> *ptrToDeleteLater) : ptr(ptrToDeleteLater), prev(nullptr) {}

    ~RetiredPointer() {
        delete ptr;
    }
};

void AddToRetiredList(RetiredPointer *newRetired) {
    while (true) {
        newRetired->prev = RetiredListHead_.load(std::memory_order_acquire);

        if (RetiredListHead_.compare_exchange_weak(newRetired->prev, newRetired, std::memory_order_release)) {
            break;
        }
    }
}

void DeleteLater(StackNode<T> *ptrToDelete) {
    AddToRetiredList(new RetiredPointer {ptrToDelete});
}

void DeleteRetired() {
    RetiredPointer *curRetiredListHead = RetiredListHead_.exchange(nullptr);

    while (curRetiredListHead) {
        RetiredPointer *prevHead = curRetiredListHead->prev;

        if (hazardPointers_.IsHazard(curRetiredListHead->ptr)) {
            delete curRetiredListHead;
        }
        else {
            AddToRetiredList(curRetiredListHead);
        }

        curRetiredListHead = prevHead;
    }
}

// =================== LOCK FREE STACK FIELDS ===================
    HazardPointers hazardPointers_;

    std::atomic<RetiredPointer *> RetiredListHead_;

    std::atomic<StackNode<T> *> head = nullptr;
};

HazardPtr hazardPointersArray[MAX_HAZARDS_COUNT];

#endif
