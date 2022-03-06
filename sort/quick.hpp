#ifndef SORT_QUICK_HPP_
#define SORT_QUICK_HPP_

#include "common.h"

static int partition(int *arr, int left, int right, int pivot)
{
    int i = left;
    int j = right;
    int pivotVal = arr[pivot];

    while (i <= j)
    {
        // keep moving i up till you find an element larger than the pivot
        while (arr[i] < pivotVal)
        {
            i++;
        }

        // keep moving j down till you find an element smaller than the pivot
        while (arr[j] > pivotVal)
        {
            j--;
        }

        if (i <= j)
        {
            swap(&arr[i], &arr[j]);
            i++;
            j--;
        }
    }

    // Return the partition point
    return i;
}

static void quick(int *arr, int left, int right)
{
    // base condition to end recursion
    if (left >= right)
        return;

    // can be randomly chosen but we will go with the midpoint
    int pivot = (left + right) / 2;

    int partitionPoint = partition(arr, left, right, pivot);

    // done swapping about the pivot, now split the array into two: the left
    // has elements smaller than the pivot, the right has elements greater than
    // the pivot; sort these in parallel.
    quick(arr, left, partitionPoint - 1);
    quick(arr, partitionPoint, right);
}

void Sort_quick(int *arr, int arrSize)
{
    int left = 0;
    int right = arrSize - 1;
    quick(arr, left, right);
}

#endif /* SORT_QUICK_HPP_ */