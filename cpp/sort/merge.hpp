#ifndef SORT_MERGE_HPP_
#define SORT_MERGE_HPP_

static void combine(int *arr, int start, int mid, int end)
{
    int *buffer = new int[end + 1];
    int k = start;

    while (k <= end)
    {
        buffer[k] = arr[k];
        k++;
    }

    //              i               j
    //              v               v
    //             +---+---+       +---+---+
    //             | 1 | 4 |       | 2 | 5 |
    //             +---+---+       +---+---+
    //
    //                 +---+---+---+---+
    //                 |   |   |   |   |
    //                 +---+---+---+---+
    //                   ^
    //                   k
    int i = start;
    int j = mid + 1;
    k = start;

    while ((i <= mid) && (j <= end))
    {
        if (buffer[i] < buffer[j])
        {
            // place a[i] at the kth position in the sorted array and advance it
            arr[k] = buffer[i];
            i++;
        }
        else // (buffer[i] > buffer[j])
        {
            // place a[j] at the kth position in the sorted array and advance it
            arr[k] = buffer[j];
            j++;
        }
        k++;
    }

    //  i past mid, j still has more-- append a[j] to end of sorted array
    //
    //                       i            j
    //                       v            v
    //             +---+---+       +---+---+
    //             | 1 | 4 |       | 2 | 5 |
    //             +---+---+       +---+---+
    //
    //                 +---+---+---+---+
    //                 | 1 | 2 | 4 |   |
    //                 +---+---+---+---+
    //                               ^
    //                               k
    while (j <= end)
    {
        arr[k] = buffer[j];
        j++;
        k++;
    }

    //  j past end, i still has more-- append a[i] to end of sorted array
    while (i <= mid)
    {
        arr[k] = buffer[i];
        i++;
        k++;
    }

    delete[] buffer;
}

static void merge(int *arr, int start, int end)
{
    // base case to end recursion
    if (start >= end)
        return;

    // Find the midpoint of the array
    int mid = (start + end) / 2;

    // sort the two halves separately
    merge(arr, start, mid);
    merge(arr, mid + 1, end);

    // put them together
    combine(arr, start, mid, end);
}

//                 +---+---+---+---+
//                 | 4 | 1 | 5 | 2 |
//                 +---+---+---+---+
// split                /    \
//             +---+---+       +---+---+
//             | 4 | 1 |       | 5 | 2 |
//             +---+---+       +---+---+
// sort            v               v
//             +---+---+       +---+---+
//             | 1 | 4 |       | 2 | 5 |
//             +---+---+       +---+---+
// combine              \     /
//                 +---+---+---+---+
//                 | 1 | 2 | 4 | 5 |
//                 +---+---+---+---+
//
void Sort_merge(int *arr, int arrSize)
{
    merge(arr, 0, arrSize - 1);
}

#endif /* SORT_MERGE_HPP_ */