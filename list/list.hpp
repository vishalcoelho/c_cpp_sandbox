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

    int GetSize() const { return size; }

    bool IsEmpty() const { return (0 == GetSize()); }

    void AddLast(T &elem)
    {
        Node<T> *node = new Node<T>(elem);

        if (IsEmpty())
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

    T RemoveLast(void)
    {
        if (IsEmpty())
            throw std::runtime_error("List is empty");

        Node<T> *node = tail;

        T retval = node->data;
        tail = node->prev;
        node->prev = NULL;
        size--;

        delete node;

        return retval;
    }

    T RemoveFirst(void)
    {
      if (IsEmpty())
            throw std::runtime_error("List is empty");

        Node<T> *node = head;

        T retval = node->data;
        head = node->next;
        node->next = NULL;
        size--;

        delete node;

        return retval;
    }

    T PeekLast(void) const
    {
        if (IsEmpty())
            throw std::runtime_error("List is empty");

        Node<T> *node = tail;
        T retval = node->data;

        return retval;
    }

    T PeekFirst(void) const
    {
        if (IsEmpty())
            throw std::runtime_error("List is empty");

        Node<T> *node = head;
        T retval = node->data;

        return retval;
    }

private:
    Node<T> *head;
    Node<T> *tail;

    int size;
};

#endif /* LIST_HPP_ */
