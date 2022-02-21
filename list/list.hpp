#ifndef LIST_HPP_
#define LIST_HPP_

#include <stdexcept>

/**
 * @brief Abstact Data Type implmented as a doubly-linked list.
 * @author Vishal Coelho
 */
template <typename T>
struct Node
{
    Node(const T &val) : data(val), next(NULL), prev(NULL) {}

    T data;
    Node<T> *next;
    Node<T> *prev;
};

template <typename T>
class List
{
public:
    List() : head(NULL), tail(NULL), size(0) {}

    int getSize() { return size; }

    bool isEmpty() { return (0 == getSize()); }

    void addLast(T &elem)
    {
        Node<T> *node = new Node<T>(elem);

        if (isEmpty())
        {
            head = node;
        }
        else
        {
            node->prev = tail;
            tail->next = node;
        }
        tail = node;
        size++;
    }

    T removeLast(void)
    {
        if (isEmpty())
            throw std::runtime_error("List is empty");

        Node<T> *node = tail;

        T retval = tail->data;
        tail = node->prev;
        node->prev = NULL;
        size--;

        delete node;

        return retval;
    }

    T peekLast(void)
    {
        if (isEmpty())
            throw std::runtime_error("List is empty");

        Node<T> *node = tail;
        T retval = tail->data;

        return retval;
    }

private:
    Node<T> *head;
    Node<T> *tail;

    int size;
};

#endif /* LIST_HPP_ */
