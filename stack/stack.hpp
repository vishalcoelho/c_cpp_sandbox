#ifndef STACK_HPP_
#define STACK_HPP_

#include "../list/list.hpp"

/**
 * @brief Abstract Data Type Stack Implementation using a singly linked list.
 * 
 * This stack is implemented with a doubly linked list. It doesn't have a max
 * cap at the moment.
 */

template <typename T>
class Stack : public List<T>
{
public:
    int size() { return list.getSize(); }

    void push(T elem) { list.addLast(elem);}

    T pop(void) {
        if (list.isEmpty())
            throw std::runtime_error("Stack is empty");
        return (list.removeLast());
    }

    bool isEmpty() { return (list.isEmpty()); }

    T peek() {
        if (list.isEmpty())
            throw std::runtime_error("Stack is empty");
        return (list.peekLast());
    }

private:
    List<T> list;
};

#endif /* STACK_HPP_ */