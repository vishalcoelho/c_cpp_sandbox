#ifndef COMMON_H_
#define COMMON_H_

extern "C" inline void swap(int *posA, int *posB)
{
    int temp = *posA;
    *posA = *posB;
    *posB = temp;
}

#endif // COMMON_H_