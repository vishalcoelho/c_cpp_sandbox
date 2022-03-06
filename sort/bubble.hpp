#ifndef SORT_BUBBLE_HPP_
#define SORT_BUBBLE_HPP_

static bool bubble(int *arr, int arrSize)
{
    bool retval = true;
    int i = arrSize - 1;
    while (i)
    {
        //          i-1
        //           | > i
        //           v   v
        // +---+---+---+---+
        // | 3 | 4 | 2 | 1 | : swap
        // +---+---+---+---+
        if (arr[i] < arr[i - 1])
        {
            swap(&arr[i], &arr[i - 1]);
            // swap happened, indicate that in the return.
            retval = false;
        }

        i--;
    }
    return retval;
}

void Sort_bubble(int *arr, int arrSize)
{
    int repititions = 0;
    while (repititions < arrSize - 1)
    {
        if (bubble(arr, arrSize))
            // no more swaps
            break;
        repititions++;
    }
}

#endif /* SORT_BUBBLE_HPP_ */