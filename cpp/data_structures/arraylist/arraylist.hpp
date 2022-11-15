#ifndef ARRAY_LIST_H_
#define ARRAY_LIST_H_

#include <string.h>

/**
 * @brief Array List implementation.
 * @author Vishal Coelho
 */
template <typename T>
class ArrayList
{
public:
    ArrayList(): size(0), capacity(0), array(nullptr) {}

    ArrayList(int size): size(0), capacity(size), array(new T[size]) {}

    ArrayList &operator=(const ArrayList &obj);

    int GetSize() const { return size; }

    int GetCapacity() const { return capacity; }

    void Add(T value) {
        if (size >= capacity)
            throw std::out_of_range("Exceeded bounds of ArrayList.");

        array[size++] = value;
    }

    void Set(int index, T value)
    {
        if (index >= capacity)
            throw std::out_of_range("Exceeded bounds of ArrayList.");

        array[index] = value;
    }

    T Get(int index)
    {
        if (index >= capacity)
            throw std::out_of_range("Exceeded bounds of ArrayList.");

        return array[index];
    }

    void Clear()
    {
        memset(array, 0, size);
        size = 0;
    }

private:
    T *array = nullptr;

    int size = 0;
    int capacity = 0;
};

template <typename T>
ArrayList<T> &ArrayList<T>::operator=(const ArrayList<T> &obj)
{
    delete[] array;
    array = new T[obj.GetSize()];
    std::copy(obj.array, obj.array + obj.size, array);
    size = obj.GetSize();
    capacity = obj.GetCapacity();

    return *this;
}

#endif /* ARRAY_LIST_H_ */
