#ifndef SORT_SIMPLE_HPP_
#define SORT_SIMPLE_HPP_

#include "common.h"

void Sort_simple(int *arr, int arrSize)
{
    for (int i = 0; i < arrSize - 1; i++)
    {
        for (int j = i + 1; j < arrSize; j++)
        {
            if (arr[i] > arr[j])
                swap(&arr[i], &arr[j]);
        }
    }
}

#endif // SORT_SIMPLE_HPP_