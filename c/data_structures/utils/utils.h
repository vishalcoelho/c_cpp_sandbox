#ifndef UTILS_H_
#define UTILS_H_

static inline void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static inline void swapRows(int **a, int **b)
{
    int *temp = *a;
    *a = *b;
    *b = temp;
}

static inline int magnitudeSquared(int x, int y)
{
    return (x * x + y * y);
}

#endif /* UTILS_H_ */