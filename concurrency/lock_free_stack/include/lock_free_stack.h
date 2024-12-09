#ifndef CONCURRENCY_LOCK_FREE_STACK_CONTAINERS_INCLUDE_LOCK_FREE_STACK_H
#define CONCURRENCY_LOCK_FREE_STACK_CONTAINERS_INCLUDE_LOCK_FREE_STACK_H

#include <optional>
#include <stdio.h>

template<class T>
struct StackNode {
    T data;
    StackNode *prev;

    StackNode(T val, StackNode *newPrev) : data(val), prev(newPrev) {}
};

template<class T>
class LockFreeStack {
public:

    void Push([[maybe_unused]] T val) {
        StackNode<T> *newNode = new StackNode<T> {val, nullptr};

        while (true) {
            newNode->prev = head.load(std::memory_order_release);

            if (head.compare_exchange_weak(newNode->prev, newNode, std::memory_order_acquire)) {
                break;
            }
        }
    }

    std::optional<T> Pop() {
        StackNode<T> *oldHead;

        T valueToReturn;

        do {
            oldHead = head.load(std::memory_order_release);

            if (oldHead == nullptr) {
                return std::nullopt;
            }

            valueToReturn = oldHead->data;

            if (head.compare_exchange_weak(oldHead, oldHead->prev, std::memory_order_acquire)) {
                break;
            }
        } while (true);

        return valueToReturn;
    }

    bool IsEmpty() {
        return head == nullptr;
    }

private:
    std::atomic<StackNode<T> *> head = nullptr;
};

#endif
