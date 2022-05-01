#include "heap.h"
#include "utils/utils.h"

#include <stdio.h>
#include <stdlib.h>

/** Fixed column width of each heap entry.
 *
 *  This allows us to specify the 2-D array argument as a pointer to an array
 *  of type int [COLS]
 *      void fxn(int (*p)[COLS])
 * Alternatively, C99 allows variable size array arguments if you pass in all
 * the matrix dimension--except the first--prior to the matrix itself.
 *      void fxn(int rows, int cols, int p[][cols])
 *
 *  If using the double pointer as the 2-D matrix argument you cannot specify
 *  the argument as a int arr[][2]. int arr[][2] has all its rows concatenated
 *  in the same memory and does not exist as array of pointers to int[2].
 */
#define COLS (2)

//     +-i/2-+--+
//     |     |  |
//  +--v---+-*+-*+--+--+--+--+---+---+---+---+
//  | P    | L|R |LL|LR|RL|RR|LLL|LLR|LRL|LRR|...
//  +-*----+-^+-^+--+--+--+--+---+---+---+---+
//    +-2i---+  |
//    +-2i+1----+

extern void heapifyMin(int **heap, int heapSize, int i)
{
    int parent = i;
#if DEBUG
    printf("At parent:%d->(%d,%d)\n", parent, heap[parent][0], heap[parent][1]);
#endif
    int left = leftChildIndex(i);
    int right = rightChildIndex(i);
    int smallest = parent;

    int msqL, msqR, msqS;
    msqS = magnitudeSquared(heap[parent][0], heap[parent][1]);
    if (left < heapSize)
    {
        msqL = magnitudeSquared(heap[left][0], heap[left][1]);
        // is left child smallest?
        if (msqL < msqS)
        {
            smallest = left;
            msqS = msqL;
        }
    }

    if (right < heapSize)
    {
        msqR = magnitudeSquared(heap[right][0], heap[right][1]);

        // is right child smallest?
        if (msqR < msqS)
        {
            smallest = right;
        }
    }

    // if smallest was not the parent, exchange the smallest child with the
    // parent. Now we have an inbalance at the child location, heapify that!
    if (smallest != parent)
    {
        swapRows(&heap[smallest], &heap[parent]);
#if DEBUG
        printf("SWAP:%d<->%d\n", smallest, parent);
#endif
        heapifyMin(heap, heapSize, smallest);
    }
#if DEBUG
    printf("P:%d:(%d,%d), ", magnitudeSquared(heap[smallest][0], heap[smallest][1]), heap[smallest][0], heap[parent][1]);
    if (left < heapSize)
        printf("L:%d:(%d,%d), ", magnitudeSquared(heap[left][0], heap[left][1]), heap[left][0], heap[left][1]);
    if (right < heapSize)
        printf("R:%d:(%d,%d), ", magnitudeSquared(heap[right][0], heap[right][1]), heap[right][0], heap[right][1]);
    printf("\n");
#endif
}

int *pop(int **heap, int *heapSize)
{
    int *retval = heap[0];

    // exchange root with the last leaf node
    heap[0] = heap[(*heapSize) - 1];
    (*heapSize)--;

    // heapify from the root.
    heapifyMin(heap, *heapSize, 0);

    return retval;
}

void printInOrder(int **heap, int heapSize, int root)
{
    int left = leftChildIndex(root);
    int right = rightChildIndex(root);

    if (left < heapSize)
        printInOrder(heap, heapSize, left);

    if (root < heapSize)
        printf("%d:(%d,%d), ", magnitudeSquared(heap[root][0], heap[root][1]), heap[root][0], heap[root][1]);

    if (right < heapSize)
        printInOrder(heap, heapSize, right);
}

void printPreOrder(int **heap, int heapSize, int root)
{
    int left = leftChildIndex(root);
    int right = rightChildIndex(root);

    if (root < heapSize)
        printf("%d:(%d,%d), ", magnitudeSquared(heap[root][0], heap[root][1]), heap[root][0], heap[root][1]);

    if (left < heapSize)
        printPreOrder(heap, heapSize, left);

    if (right < heapSize)
        printPreOrder(heap, heapSize, right);
}

void printPostOrder(int **heap, int heapSize, int root)
{
    int left = leftChildIndex(root);
    int right = rightChildIndex(root);

    if (left < heapSize)
        printPostOrder(heap, heapSize, left);

    if (right < heapSize)
        printPostOrder(heap, heapSize, right);

    if (root < heapSize)
        printf("%d:(%d,%d), ", magnitudeSquared(heap[root][0], heap[root][1]), heap[root][0], heap[root][1]);
}

// Unit Tests
#include <time.h>
static void printArray(int **arr, int arrSize);

int main(void)
{
    time_t t;
    srand((unsigned)time(&t));

    int n_rows = 6;
    int **arr = (int **)malloc(sizeof(int[COLS]) * n_rows);
    for (int i = 0; i < n_rows; i++)
    {
        arr[i] = (int *)malloc(sizeof(int) * COLS);
        arr[i][0] = rand() % n_rows;
        arr[i][1] = rand() % (n_rows + n_rows);
    }
    int heapSize = n_rows;
    printf("heap size = %d\n", heapSize);
    printArray(arr, heapSize);

    // all the elements, heapSize/2 -> heapSize-1 are leaf nodes--heaps of size
    // 1--and dont need to be ordered, so we start heapifying from node
    // heapSize/2 -1 and work our way to the root.
    for (int i = (heapSize / 2) - 1; i >= 0; i--)
        heapifyMin(arr, heapSize, i);

    printArray(arr, heapSize);
    printf("\n");

    // Pop all the elements in min order
    while (heapSize)
    {
        int *row = pop(arr, &heapSize);
        printf("%d:(%d,%d), ", magnitudeSquared(row[0], row[1]), row[0], row[1]);
    }

    return 0;
}

static void printArray(int **arr, int arrSize)
{
    for (int i = 0; i < arrSize; i++)
        printf("%d:(%d,%d), ", magnitudeSquared(arr[i][0], arr[i][1]), arr[i][0], arr[i][1]);
    printf("\n");
}