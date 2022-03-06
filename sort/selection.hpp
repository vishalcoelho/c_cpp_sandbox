#ifndef SORT_SELECTION_HPP_
#define SORT_SELECTION_HPP_

#include "common.h"

static int locateSmallestIndex(int *arr, int start, int end)
{
    int min = arr[start];
    int minIndex = start;
    for (int i = start + 1; i <= end; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
            minIndex = i;
        }
    }

    return minIndex;
}

void Sort_selection(int *arr, int arrSize)
{
    int i = 0;
    while (i < arrSize - 1)
    {
        int j = locateSmallestIndex(arr, i, arrSize - 1);
        if (i != j)
            swap(&arr[i], &arr[j]);
        i++;
    }
}

#endif // SORT_SELECTION_HPP_