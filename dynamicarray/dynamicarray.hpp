#ifndef DYNAMICARRAY_HPP_
#define DYNAMICARRAY_HPP_

#if __cplusplus < 201103L
#error "You need C++11 or greater for this module to work"
#endif

#include <stdexcept>
#include <string>

/**
 * @brief Dynamic Array implementation.
 * @author Vishal Coelho
 *
 * This dynamic array doubles when capacity is reached. It has no max cap--unless you
 * run out of heap--and it can only grow, never shrink.
 */

template <typename T>
class DynamicArray
{
public:
    static constexpr int DEFAULT_DYNAMIC_ARRAY_SIZE = 100U;

    DynamicArray(int capacity) : length(0)
    {
        if (0 > capacity)
            throw std::runtime_error("Can't have negative capacity");

        construct(capacity);
    }

    /* Looks like i cant have the default constructor call the override;
     * if i try to create an obj(2) it ends up calling this contructor recursively
     * till i run out of stack.
     *
     * Ended up writing a common private construct function that gets called int
     * both constructors.
     *
     * DynamicArray() { DynamicArray(DEFAULT_DYNAMIC_ARRAY_SIZE); }
     */

    DynamicArray() : length(0) { construct(DEFAULT_DYNAMIC_ARRAY_SIZE); }

    int getSize() { return length; }

    int getCapacity() { return capacity; }

    bool isEmpty() { return (0 == getSize()); }

    T get(int index)
    {
        if (index >= length)
            throw std::out_of_range("Haven't added enough elements to the array");
        return array[index];
    }

    void set(int index, T value)
    {
        if (index >= length)
            throw std::out_of_range("Haven't added enough elements to the array");
        array[index] = value;
    }

    void clear()
    {
        memset(array, 0, capacity);
        length = 0;
    }

    void append(T value)
    {
        if (length == capacity)
        {
            doubleCapacity();
            resizeArray();
        }
        array[length++] = value;
    }

    T removeAt(int index)
    {
        if (index > length)
            throw std::out_of_range("Exceeded bounds.");

        T retval = array[index];
        std::copy(array + index + 1, array + length, array + index);
        length--;

        return retval;
    }

    bool contains(T value)
    {
        bool retval = false;
        if (-1 != indexOf(value))
            retval = true;
        return retval;
    }

private:
    void construct(int capacity)
    {
        this->capacity = capacity;
        this->array = new T[capacity];
    }

    void doubleCapacity(void)
    {
        if (0 == capacity)
            capacity = 1;
        else
            capacity *= 2;
    }

    void resizeArray(void)
    {
        T *new_array = new T[capacity];
        std::copy(array, array + length, new_array);
        delete[] array;

        array = new_array;
    }

    int indexOf(T value)
    {
        int retval = -1;
        for (auto i = 0; i < length; i++)
        {
            if (array[i] == value)
            {
                retval = i;
                break;
            }
        }
        return retval;
    }

    T *array;
    int length;
    int capacity;
};

#endif /* DYNAMICARRAY_HPP_ */
