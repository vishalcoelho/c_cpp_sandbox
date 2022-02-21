#ifndef QUEUE_HPP_
#define QUEUE_HPP_

#include "../list/list.hpp"

/**
 * @brief Abstract Data Type Queue Implementation using a singly linked list.
 * @author Vishal Coelho
 * 
 * This queue is implemented with a doubly linked list. It doesn't have a max
 * cap at the moment.
 */

template <typename T>
class Queue
{
public:
    int GetSize() const { return list.GetSize(); }

    void Enqueue(T elem) { list.AddLast(elem); }

    T Dequeue(void)
    {
        if (list.IsEmpty())
            throw std::runtime_error("Queue is empty");
        return (list.RemoveFirst());
    }

    bool IsEmpty() const { return (list.IsEmpty()); }

    T Peek() const
    {
        if (list.IsEmpty())
            throw std::runtime_error("Queue is empty");
        return (list.PeekFirst());
    }

private:
    List<T> list;
};

#endif /* QUEUE_HPP_ */