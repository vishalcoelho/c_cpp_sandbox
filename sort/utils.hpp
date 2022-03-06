#ifndef SORT_UTILS_HPP_
#define SORT_UTILS_HPP_

#include <string>
#include <time.h>

#define NANOSECONDS_PER_SEC ((double)1000000000)

class Utils
{
public:
    Utils() : arr(NULL), arrSize(0) {}

    Utils(int *arr, int arrSize) : arr(arr), arrSize(arrSize) {}

    void PrintArray(void)
    {

        for (int i = 0; i < arrSize; i++)
            printf("%d, ", arr[i]);

        printf("\n\n");
    }

    /* Signature of pretty much every sorting function. */
    typedef void (*SortFxn)(int *arr, int arrSize);

    void Benchmark(SortFxn fxn)
    {
        start = time(NULL);
        fxn(arr, arrSize);
        end = time(NULL);

        timeElapsedNsec = (difftime(end, start) / CLOCKS_PER_SEC) * NANOSECONDS_PER_SEC;

        printf("Start: %ld, End: %ld, Time elapsed: %ld\n\n", start, end, timeElapsedNsec);
    }

private:
    int *arr;
    int arrSize;

    time_t start, end;
    double timeElapsedNsec;
};

#endif /* SORT_UTILS_HPP_ */