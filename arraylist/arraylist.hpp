#ifndef ARRAY_LIST_H_
#define ARRAY_LIST_H_

/**
 * @brief Array List implementation.
 * @author Vishal Coelho
 */
template <typename T>
class ArrayList
{
public:
    ArrayList(): currIndex(0), size(0), capacity(0), array(nullptr) {}

    ArrayList(int size): currIndex(0), size(size), capacity(size), array(new T[size]) {}

    int GetSize() const { return size; }

    int GetCapacity() const { return capacity; }

    void Add(T value) {
        if (currIndex >= capacity)
            throw std::out_of_range("Exceeded bounds of ArrayList.");

        array[currIndex++] = value;
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

private:
    T *array;

    int currIndex;
    int size;
    int capacity;
};

#endif /* ARRAY_LIST_H_ */
