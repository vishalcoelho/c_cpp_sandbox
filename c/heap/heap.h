#ifndef HEAP_H_
#define HEAP_H_

/** return index of the left child of parent i. */
static inline int leftChildIndex(int i)
{
    return 2 * i + 1;
}

/** return index of the right child of parent i. */
static inline int rightChildIndex(int i)
{
    return 2 * i + 2;
}

/** Sort the heap with smallest at the root.
 *
 *  Each entry in the heap is a 2-d co-ordinate.
 */
extern void heapifyMin(int **heap, int heapSize, int i);

/** Sort the heap with largest at the root. */
extern void heapifyMax(int **heap, int heapSize, int i);

/** Return the root of the heap. */
extern int *pop(int **heap, int *heapSize);

/** Print heap in order.
 *   A
 *  / \
 * B   C
 *
 * B->A->C
 */
extern void printInOrder(int **heap, int heapSize, int root);

/** Print heap in pre-order.
 *   A
 *  / \
 * B   C
 *
 * A->B->C
 */
extern void printPreOrder(int **heap, int heapSize, int root);

/** Print heap in post-order.
 *   A
 *  / \
 * B   C
 *
 * B->C->A
 */
extern void printPostOrder(int **heap, int heapSize, int root);

#endif // HEAP_H_